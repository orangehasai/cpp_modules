# cpp_module04 lecture

## この lecture の目的

`cpp_module04` の主題は次の 3 つです。

- subtype polymorphism
- abstract class
- interface に相当する pure abstract class

ただし、本当に理解すべきなのは
「`virtual` を付けると便利」
という表面的な話ではありません。

この module で重要なのは次です。

- 基底クラスのポインタ越しに、なぜ派生クラスの関数が呼ばれるのか
- `virtual` が付いていないと何が壊れるのか
- オブジェクトのコピーで、なぜ shallow copy が危険なのか
- 抽象クラスは何のためにあるのか
- interface 風の設計で、依存関係と所有権をどう整理するのか

`cpp_module04/sample/` のコードは、課題を通すためだけでなく、
peer evaluation で「なぜその設計なのか」を説明できるように作ってあります。

## module04 全体の流れ

各 exercise の役割は次の通りです。

- `ex00`: virtual function による正しい動的ディスパッチ
- `ex01`: 派生クラスが動的メモリを持つときの deep copy
- `ex02`: 基底クラスを abstract class にする
- `ex03`: interface と ownership を含む設計の総復習

つまり module04 は、
Module 03 までで学んだ継承の上に
「実行時多態」
「抽象化」
「コピー責務」
を乗せる module です。

## まず結論: 多態とは「同じ呼び出し文で、実体に応じて動く」こと

たとえば次のコードを考えます。

```cpp
const Animal* a = new Dog();
a->makeSound();
```

ここで大事なのは、
変数 `a` の**静的型**は `const Animal*` であることです。

一方で、`new Dog()` で作られた実体の**動的型**は `Dog` です。

`makeSound()` が `virtual` なら、
呼び出し先は実行時に `Dog::makeSound()` に解決されます。

`virtual` でなければ、
コンパイラは静的型 `Animal*` を見て
`Animal::makeSound()` を直接呼びます。

`WrongAnimal` / `WrongCat` は、この差を見せるための対照実験です。

## C エンジニア向け: なぜ virtual で動的 dispatch が起こるのか

規格上の厳密なメモリ配置は処理系依存ですが、
学習段階では次の理解で十分です。

```text
Dog object
|- Animal subobject
|  |- type
|  `- vptr  ----> Dog 用 vtable
`- Dog 固有部分
```

多くの実装では、`virtual` 関数を持つオブジェクトは
内部に `vptr` と呼ばれる隠しポインタを持ちます。

この `vptr` は、その実体の仮想関数表 `vtable` を指します。

`a->makeSound()` のような呼び出しでは、
実行時に

1. `a` が指すオブジェクトの `vptr` を読む
2. `vtable` の `makeSound` スロットを見る
3. そこに入っている関数アドレスへ飛ぶ

という流れで関数が決まります。

だから、変数の型が `Animal*` でも、
実体が `Dog` なら `Dog::makeSound()` が呼ばれます。

### `Animal vtable` と `Dog vtable` は両方オブジェクト内に入るのか

入りません。

ここは誤解しやすいので、言い切っておきます。

- `vtable` はクラスごとに共有される表
- オブジェクトの中にあるのは表そのものではなく `vptr`
- 単純な単一継承では、多くの実装で `vptr` は 1 個で済む

つまり完成済みの `Dog` オブジェクトは、
概念的には次のように考えます。

```text
[共有領域]
Animal vtable
Dog vtable

[Dog object]
Animal subobject
|- type
`- vptr ----> Dog vtable
```

重要なのは、
`Dog` オブジェクト内の `Animal` 部分にある `vptr` が、
完成後は通常 `Dog vtable` を指していることです。

したがって

```cpp
Animal* a = new Dog();
a->makeSound();
```

では `a` の静的型は `Animal*` でも、
実体側の `vptr` が `Dog` 用テーブルを指すので
`Dog::makeSound()` に飛びます。

### では `Animal vtable` はいつ使われるのか

主に次の場面です。

- `Animal` 単体オブジェクトを作ったとき
- `Dog` 構築中に `Animal::Animal()` が動いている間
- `Dog` 破棄中に `Animal::~Animal()` が動いている間

学習段階では、
「完成済み `Dog` は `Dog` としての `vptr` 状態にある」
と理解しておけば十分です。

### constructor / destructor 中の virtual 呼び出しが危険な理由

constructor や destructor の実行中は、
オブジェクトがまだ完全な派生型ではない、あるいは
すでに派生部分の破棄が終わっている途中段階です。

そのため多くの実装では、
その時点のクラスに対応した `vptr` 状態で virtual 呼び出しが行われます。

つまり基底 constructor 内で virtual 関数を呼んでも、
「まだ `Dog` として完成していない」ので
`Dog` override に飛ぶ前提で考えてはいけません。

42 の module04 ではそこまで凝ったコードは不要ですが、
`virtual` は「常に一番下の派生へ飛ぶ魔法」ではない、
という認識は持っておくべきです。

## ex00: virtual を付ける場所が本質

`ex00` では `Animal`, `Dog`, `Cat` と
`WrongAnimal`, `WrongCat` を比較します。

ここで理解すべきポイントは次です。

- `makeSound()` を基底クラスで `virtual` にすると、派生先で override される
- `WrongAnimal::makeSound()` を non-virtual にすると、基底ポインタ越しに多態が壊れる
- 基底クラスの destructor も `virtual` にしておくのが安全

### なぜ destructor に virtual が必要なのか

次のコードを見ます。

```cpp
Animal* a = new Dog();
delete a;
```

`delete` は

1. どの destructor を呼ぶか
2. 何バイト解放するか

を正しく扱う必要があります。

基底 destructor が `virtual` なら、
実体 `Dog` に対応した destructor chain が走ります。

```text
Dog::~Dog()
-> Animal::~Animal()
-> operator delete
```

これが non-virtual だと、
`Animal::~Animal()` しか呼ばれない危険があります。
派生側が heap 資源を持っていたら、それだけでリークや未定義動作の入口です。

### 派生側にも `virtual` は必要か

言語仕様上は必須ではありません。

基底クラスで `virtual` な関数を、
派生クラスが同じシグネチャで再定義すれば、
その関数は自動的に virtual のままです。

```cpp
class Animal
{
  public:
	virtual void makeSound(void) const;
};

class Dog : public Animal
{
  public:
	void makeSound(void) const;
};
```

これは問題なく override です。

ただし C++98 には `override` キーワードがないため、
sample では可読性のために派生側ヘッダでも `virtual` を残しています。

要するに次です。

- 基底側の `virtual`: 意味の本体
- 派生側の `virtual`: 省略可能だが意図を見やすくする注記

## override と隠蔽は別物

この 2 つは初心者がかなり混同しやすい点です。

- override: virtual 関数の振る舞い差し替え
- 隠蔽: 同名関数を派生に置いた結果、基底の同名関数が見えにくくなること

もっと雑に言えば、

- override は「実行時にどこへ飛ぶか」の話
- 隠蔽は「名前探索で何が候補に出るか」の話

### override の条件

override になるには次が必要です。

- 基底クラス側の関数が `virtual`
- 派生クラス側が同じシグネチャで再定義する

```cpp
class Animal
{
  public:
	virtual void makeSound(void) const;
};

class Cat : public Animal
{
  public:
	void makeSound(void) const;
};
```

これなら

```cpp
Animal* a = new Cat();
a->makeSound();
```

で `Cat::makeSound()` が呼ばれます。

### 隠蔽は「同名」で起きる

基底関数が non-virtual でも、
あるいは引数や `const` が違っていても、
派生に同名関数が現れると基底の同名関数は隠れます。

```cpp
class Animal
{
  public:
	std::string getType(void) const;
	void move(int distance);
};

class Cat : public Animal
{
  public:
	std::string getType(void) const;
	void move(double distance);
};
```

この例では

- `getType()` は non-virtual なので override ではなく隠蔽
- `move(double)` も `move` という同名が出た時点で `Animal::move(int)` を隠す

ことになります。

つまり
**同じ名前だから即 override**
ではありません。

### `virtual` でもシグネチャが違えば override されない

特に危険なのはこれです。

```cpp
class Base
{
  public:
	virtual void f(void) const;
};

class Derived : public Base
{
  public:
	void f(void);
};
```

`const` が違うので、これは override ではありません。
`Derived::f()` が `Base::f() const` を隠しているだけです。

C++11 以降なら `override` で防ぎやすいですが、
module04 は C++98 なので自分で厳密に見る必要があります。

### 使い分け

実務感覚に寄せて短く言うと次です。

- 基底ポインタ越しでも派生の振る舞いにしたい: override
- 基底実装で十分: 派生で何も書かない
- 派生専用の別物を同名で生やす: 隠蔽になるが事故りやすいので慎重に使う

`ex00` の `makeSound()` は override 対象で、
`getType()` は基底実装をそのまま使えば十分な関数です。

## `protected` でも基底メンバを初期化リストで直接初期化はできない

これも継承直後によく迷う点です。

`protected` は
「派生クラスのメンバ関数からアクセスしてよい」
という意味であって、
「派生クラスの初期化リストで直接初期化してよい」
という意味ではありません。

たとえば基底が

```cpp
class Animal
{
  protected:
	std::string type;
};
```

でも、派生で

```cpp
Cat::Cat() : type("Cat")
{
}
```

とは書けません。

理由は、派生クラスの初期化リストで直接指定できるのは次だけだからです。

- 直接の基底クラス
- その派生クラス自身のメンバ

`type` は `Cat` 自身のメンバではなく、
`Animal` サブオブジェクトのメンバです。

したがって sample のように

```cpp
Cat::Cat() : Animal()
{
	type = "Cat";
}
```

とは書けますが、
これは「基底構築後に代入している」だけです。

もし最初から基底側で型名を入れたいなら、
基底に受け口を用意します。

```cpp
class Animal
{
  public:
	Animal(const std::string &initialType);
};

Cat::Cat() : Animal("Cat")
{
}
```

設計としてきれいなのは普通はこちらです。

## 継承オブジェクトは「基底部分を含む」

`Dog` は `Animal` のコードをコピペしたものではありません。

概念的には次です。

```text
Dog
|- Animal 部分
`- Dog 独自部分
```

このため、

- `Dog` 構築時にはまず `Animal` 部分が作られる
- `Dog` 破棄時にはまず `Dog` 側が壊れ、その後 `Animal` 側が壊れる
- `Dog*` は `Animal*` に暗黙変換できる

という挙動になります。

## ex01: deep copy は「ポインタ値」ではなく「所有データ」を複製する

`ex01` では `Dog` と `Cat` が `Brain*` を持ちます。

ここが module04 前半の山場です。

### shallow copy が危険な理由

もし copy constructor / copy assignment operator が
ポインタ値だけをコピーすると、

```text
Dog A          Dog B
_brain ----+   _brain ----+
           |              |
           +----> Brain object
```

という状態になります。

これだと問題が 2 つ起きます。

- `A` が `Brain` を書き換えると `B` も変わる
- `A` と `B` の destructor が同じ `Brain` を `delete` して二重解放になる

したがって必要なのは
**ポインタ先の実体を別々に確保する deep copy**
です。

### deep copy の正しいイメージ

```text
Dog A                     Dog B
_brain ----> Brain A      _brain ----> Brain B
```

この状態なら、

- 片方の `idea` を変更しても他方に影響しない
- 各 destructor が自分の `Brain` だけを解放する

ので安全です。

### copy constructor と assignment の責務は違う

ここも C 初学者が混同しやすい点です。

#### copy constructor

まだ何も持っていない新オブジェクトを、
別オブジェクトの内容で**新規構築**します。

`Dog copied(original);`

このときは最初から `new Brain(*other._brain)` できます。

#### copy assignment operator

すでに存在しているオブジェクトへ、
別オブジェクトの内容を**上書き**します。

`a = b;`

このときは

- self-assignment を避ける
- 既存の所有資源をどう扱うか考える
- 代入後も二重解放しないようにする

が必要です。

今回の sample では、
`Dog` / `Cat` の `_brain` は constructor で常に確保済みにして、
assignment では `*_brain = *other._brain;` と
**中身だけコピー**しています。

これにより再 `new` を避けつつ deep copy を維持できます。

## ex02: abstract class は「共通土台だが、単体実体にはしたくない型」

`ex02` では `Animal` を abstract class にします。

やり方は単純で、
少なくとも 1 つ pure virtual function を持たせます。

```cpp
virtual void makeSound(void) const = 0;
```

この `= 0` が pure virtual の印です。

### abstract class になると何が起きるか

- `Animal` 型のオブジェクトは直接生成できない
- `Animal*` や `Animal&` は使える
- 派生クラスが pure virtual を override すれば具象化できる

つまり `Animal` は
「共通の interface と共通データを持つ基底」
にはなるが、
「鳴き声不明の動物そのもの」
としては存在できなくなります。

### pure virtual でも constructor / destructor は普通にある

ここはかなり重要です。

`Animal` が abstract でも、
`Dog` の中には `Animal` 部分が必ず入っています。

そのため `Animal` の constructor と destructor は普通に必要です。

```text
Dog construction
1. Animal constructor
2. Dog constructor

Dog destruction
1. Dog destructor
2. Animal destructor
```

abstract class は
「作れない class」ではなく、
「それ単体の完全な実体にはできない class」
です。

## ex03: interface は「使い方だけを固定し、実装を差し替える」ための形

C++98 には Java の `interface` キーワードはありません。
42 の文脈で interface と言うと、普通は
**pure abstract class**
を意味します。

今回の主役は次の 3 系統です。

- `AMateria`: 共通基底
- `ICharacter`: Character が満たす interface
- `IMateriaSource`: MateriaSource が満たす interface

### `AMateria` は interface ではなく abstract base class

`AMateria` は pure virtual `clone()` を持つので abstract ですが、
同時に

- `type`
- `xp`
- `getType()`
- `getXP()`
- `use()` による XP 加算

という**共通実装**も持っています。

つまり `AMateria` は
「ただの interface」
ではなく
「共通状態つき抽象基底」
です。

### XP を base class に集約する理由

subject では `use()` のたびに XP を 10 増やせと言っています。

これを `Ice` と `Cure` の両方に個別実装すると重複します。

そのため sample では

```cpp
void AMateria::use(ICharacter &target)
{
	(void)target;
	_xp += 10;
}
```

として共通化し、
派生側 `Ice::use()` / `Cure::use()` が
先に `AMateria::use(target)` を呼ぶ設計にしています。

これが subject の
`Find a smart way to handle that!`
への答えです。

## forward declaration が必要な理由

`AMateria` は `use(ICharacter&)` を持ち、
`ICharacter` は `equip(AMateria*)` を持ちます。

つまり互いに相手の型名を知りたい関係です。

ここで両ヘッダが互いを `#include` すると、
循環依存になりやすくなります。

そのため次のように前方宣言を使います。

```cpp
class ICharacter;
class AMateria;
```

### C 的に言うと何をしているか

前方宣言は
「その型の**完全な中身はまだ知らないが、名前だけはある**
とコンパイラに先に教える」
行為です。

ポインタや参照を宣言するだけなら、
完全定義は不要です。

逆に

- メンバ関数を呼ぶ
- オブジェクトを値として持つ
- `sizeof` を取る

には完全定義が必要です。

## ex03 最大の論点: raw pointer の所有権

この exercise が難しい理由の大半はここです。

### `MateriaSource::learnMateria`

sample 実装では、学習した Materia のテンプレートを
`MateriaSource` が保持し、destructor で解放します。

つまり成功時の所有権は次です。

- 呼び出し前: 呼び出し側が所有
- `learnMateria()` 成功後: `MateriaSource` が所有

`createMateria()` はそのテンプレートを `clone()` して新しい実体を返します。

### `Character::equip`

sample 実装では、
空きスロットに入った時点で Character がその Materia を所有します。

- `equip()` 成功後: Character が destructor で解放
- inventory が満杯で入らなかった場合: 呼び出し側がまだ所有

したがって、満杯時に返ってきたポインタを捨てると leak します。
`main.cpp` では失敗した `fifth` を手動 `delete` しているのはそのためです。

### `Character::unequip`

subject の重要条件は
**`unequip()` は delete してはいけない**
です。

つまり `unequip()` は

- スロットから外す
- しかしメモリは解放しない

だけを行います。

これは C 的には
「所有権を手放すが、寿命は終わらせない」
操作です。

そのため sample の `main.cpp` では

```cpp
AMateria *dropped = src->createMateria("ice");
floorTester.equip(dropped);
floorTester.unequip(0);
delete dropped;
```

と、呼び出し側がポインタを保持して後で片付けています。

## deep copy が ex03 でも必要な理由

`Character` の inventory は `AMateria*` 配列です。

ここで shallow copy すると、
複数 Character が同じ Materia 実体を指すことになります。

すると

- 片方の destructor が delete
- もう片方も同じポインタを delete

で二重解放です。

だから copy constructor / assignment operator では
各スロットを `clone()` して複製します。

### なぜ `clone()` が必要か

`AMateria*` は基底ポインタです。
しかし複製したい実体は `Ice` か `Cure` か、あるいは今後増える別型かもしれません。

ここで `new AMateria(*ptr)` はできません。
`AMateria` は abstract だからです。

必要なのは
「自分自身の実型で自分を複製する virtual 関数」
です。

それが `clone()` です。

これは OOP でいう **virtual constructor idiom** の基本形です。

## `AMateria::operator=` で type をコピーしない理由

subject は
「Materia の代入で type をコピーするのは意味がない」
と言っています。

これはかなり本質的です。

`Ice` は本質的に ice であり、
`Cure` は本質的に cure です。

代入で `type` まで自由に書き換えると、
実体は `Ice` なのに文字列だけ `"cure"` という
ねじれた状態が作れてしまいます。

sample 実装では `AMateria::operator=` で XP だけをコピーし、
`_type` は constructor で決まる実体属性として扱っています。

## interface 設計の利点

`ICharacter` と `IMateriaSource` を挟むことで、
利用側は具体型に強く依存しなくなります。

たとえば

```cpp
IMateriaSource *src = new MateriaSource();
ICharacter *hero = new Character("hero");
```

のように書けます。

この利点は次です。

- 呼び出し側は「何ができるか」だけ知ればよい
- 実装クラスを差し替えやすい
- テストコードが抽象型越しに書ける

C の関数ポインタテーブルを手で組むより、
C++ はこれを言語機能として提供していると考えると理解しやすいです。

## module04 でよくあるミス

- 基底 destructor を non-virtual にして `delete basePtr;` する
- `WrongAnimal` の `makeSound()` まで virtual にしてしまい、悪い例が成立しなくなる
- `Brain*` を shallow copy して二重解放する
- `Animal` を pure virtual にしたのに `new Animal()` しようとする
- `Character` の copy で inventory のポインタ値だけコピーする
- `unequip()` で delete してしまう
- `createMateria()` が同じテンプレート本体を返してしまう
- ヘッダ間の循環 include を前方宣言なしで作る

## peer evaluation で説明できるべきこと

最低でも次は口で説明できる状態にしておくべきです。

- `virtual` がないと `WrongAnimal` 側の関数が呼ばれる理由
- なぜ destructor にも `virtual` が必要か
- `Brain*` の deep copy をしないと何が起きるか
- abstract class と interface 風 pure abstract class の違い
- `clone()` がないと `AMateria*` の多態コピーができない理由
- `equip` / `unequip` / `learnMateria` / `createMateria` の所有権

## まとめ

`cpp_module04` は、
継承を書けるかどうかの module ではありません。

本質は

- 実行時にどの関数が呼ばれるか
- 誰が heap 上の資源を所有し、誰が解放するか
- 抽象化によって依存をどう減らすか

を理解することです。

`ex00` から `ex03` まで全部つながっています。

- `ex00`: virtual がないと多態が壊れる
- `ex01`: 多態を使う世界ではコピー責務が重くなる
- `ex02`: 共通基底を抽象化して「概念」にする
- `ex03`: 抽象 interface と raw pointer ownership を両立させる

この module を雑に終えると、
以降の C++ がずっと「なんとなく動くけど怖い」になります。
逆にここを丁寧に理解すると、
後の module の設計判断がかなり安定します。
