# cpp_module03 lecture

## この lecture の目的

`cpp_module03` の主題は **inheritance（継承）** です。

ただし、この module で本当に理解すべきなのは
「`class B : public A` と書ける」ことではありません。

重要なのは次の 5 点です。

- 派生クラスは基底クラスの何を受け継ぐのか
- `private` と `protected` の違いは何か
- コンストラクタとデストラクタはどの順番で呼ばれるのか
- 同じ名前のメンバ関数やメンバ変数が複数あるとき、何が起こるのか
- 多重継承でなぜ `virtual inheritance` が必要になるのか

この lecture は、sample コードを読む補助であると同時に、
peer evaluation で「なぜそう書いたのか」を説明するための土台です。

## Module 03 で追加された考え方

Module 02 までは「1つのクラスをどう作るか」が中心でした。
Module 03 ではそこに、

- 既存クラスを土台にして新しいクラスを作る
- 共通部分は基底クラスにまとめる
- 差分だけを派生クラスに書く

という発想が入ります。

これは OOP のかなり重要な入口です。

## まず結論: 継承は「コピー」ではない

初心者が最初に勘違いしやすいのはここです。

```cpp
class ScavTrap : public ClapTrap
{
};
```

この意味は

「`ClapTrap` のコードを文字通りコピペして `ScavTrap` に貼り付ける」

ではありません。

意味としては、

「`ScavTrap` は `ClapTrap` を基底クラスとして持ち、
`ClapTrap` の public / protected な性質を利用できる」

です。

したがって `ScavTrap` オブジェクトの中には
`ClapTrap` 部分が存在します。

## 継承したオブジェクトの中身をどう考えるか

`ScavTrap` は概念的には次のような構造です。

```text
ScavTrap
|- ClapTrap 部分
`- ScavTrap 独自部分
```

つまり `ScavTrap` の中には
**基底クラス `ClapTrap` のサブオブジェクトが 1 個入っている**
と考えると理解しやすくなります。

この見方をすると、以降の次の挙動が自然に見えてきます。

- `ScavTrap` を作る前に `ClapTrap` 部分を作る必要がある
- `ScavTrap` を壊すときは先に `ScavTrap` 側を壊し、その後 `ClapTrap` 部分が壊れる
- `ScavTrap` を `ClapTrap` として参照できる

厳密なメモリ配置そのものは処理系依存ですが、
初心者の段階では
「派生クラスの中には基底クラス部分が入っている」
と押さえておけば十分です。

## ex00: まずは基底クラスそのものを安定させる

`ex00` ではまだ継承しません。
ここでやっていることは地味ですが、後の exercise の土台です。

### `ClapTrap` が持つ状態

`ClapTrap` は最低限、次の状態を持ちます。

- 名前
- hit points
- energy points
- attack damage

この 4 つが「そのオブジェクトの現在状態」です。

`attack()` や `beRepaired()` は、
ただメッセージを出すだけではなく、
**状態を読んで、状態を更新する関数** です。

### ここで大事なこと

- HP が 0 のときは行動できない
- Energy が 0 のときも行動できない
- `takeDamage()` では HP が 0 未満にならないようにする
- `beRepaired()` と `attack()` は energy を 1 消費する

つまり、subject の文章を「状態遷移」として読む必要があります。

## Orthodox Canonical Form はこの module でも続く

Module 02 からの継続ルールとして、
特別な指示がない限りクラスは Orthodox Canonical Form で作ります。

必要なのは次の 4 つです。

- default constructor
- copy constructor
- copy assignment operator
- destructor

この module では派生クラスにもこれが必要です。

### なぜ派生クラスでも必要なのか

継承していても、オブジェクトはやはり

- 生成される
- コピーされる
- 代入される
- 破棄される

からです。

しかも派生クラスでは
**「基底クラス部分も一緒にどう扱うか」**
を意識しなければいけません。

## `private` と `protected` の違い

Module 03 で非常に大事です。

### `private`

`private` メンバは、そのクラスのメンバ関数からしか触れません。

```cpp
class ClapTrap
{
  private:
	std::string _name;
};
```

この場合、`ScavTrap` から `_name` を直接読むことはできません。

### `protected`

`protected` は

- クラス自身からは使える
- 派生クラスからも使える
- クラス外からは使えない

という中間的な公開範囲です。

### ではなぜ `ex01` 以降で `protected` を使うのか

subject に

- `ScavTrap` will use the attributes of `ClapTrap`

とあるからです。

つまり派生クラス側で

- HP を 100 に変える
- Energy を 50 に変える
- Attack damage を 20 に変える

のような初期化をしたいわけです。

そのため sample では `ex01` 以降、
属性を `protected` にしています。

### ただし `protected` は「初期化してよい」という意味ではない

ここはかなり重要です。

`protected` はあくまで
**派生クラスのメンバ関数からアクセスしてよい**
という意味です。

たとえば `ScavTrap::attack()` の中で
`_name` や `_energyPoints` を使うのは問題ありません。

しかし、だからといって `ScavTrap` の初期化リストで
基底クラスのメンバを
`ScavTrap` 自身のメンバのように直接初期化してよいわけではありません。

```cpp
ScavTrap::ScavTrap() : _name(""), _hitPoints(100)
{
}
```

これは NG です。

理由は `_name` や `_hitPoints` が
`ScavTrap` 自身のメンバではなく、
`ClapTrap` のメンバだからです。

つまり:

- `protected` はアクセス権の話
- 初期化リストは「誰を構築するか」の話

であり、別ルールです。

## 初期化リストで書けるもの

コンストラクタの `:` の右側には、
基本的に次の 2 種類しか書けません。

- 直接の基底クラス
- そのクラス自身が宣言したメンバ

たとえば `ScavTrap` なら、初期化リストに書けるのは:

- `ClapTrap(...)`
- `ScavTrap` 自身が新しく持っているメンバ

です。

逆に、`ClapTrap` が持っている `_name` などを
`ScavTrap` 側で直接

```cpp
: _name("Serena")
```

のようには書けません。

`_name` の所有者は `ClapTrap` だからです。

## `ScavTrap::ScavTrap() : ClapTrap("")` は何をしているのか

これは
**`ScavTrap` の中にある基底クラス部分 `ClapTrap` を、
どのコンストラクタで構築するか指定している**
という意味です。

```cpp
ScavTrap::ScavTrap() : ClapTrap("")
{
	_hitPoints = 100;
	_energyPoints = 50;
	_attackDamage = 20;
}
```

ここでやっているのは:

1. `ClapTrap("")` で基底クラス部分を作る
2. そのあと `ScavTrap` のコンストラクタ本体に入る
3. 本体の中で値を上書きする

です。

重要なのは、これは代入ではなく
**基底クラスの構築指定** だということです。

### 初期化リストは代入ではない

初期化リストは、
オブジェクトができあがったあとに値を入れる仕組みではありません。

流れは次の通りです。

1. 基底クラスを構築する
2. メンバを構築する
3. そのあとでコンストラクタ本体 `{ ... }` が実行される

そのため:

```cpp
ScavTrap::ScavTrap() : ClapTrap("")
{
	_hitPoints = 100;
}
```

の `_hitPoints = 100;` は
「初期化」ではなく、すでに存在している基底クラス部分への代入です。

## なぜ `ClapTrap(...)` であって `_name(...)` ではないのか

`ScavTrap` から見たとき、
`ClapTrap` は **直接の基底クラス** です。
したがって初期化リストに

```cpp
ClapTrap(...)
```

と書けます。

一方 `_name` は
`ScavTrap` 自身のメンバではありません。
あくまで `ClapTrap` のメンバです。

したがって:

- `ClapTrap(...)` は OK
- `_name(...)` は NG

になります。

### 「直接の基底クラス」だけが対象

ここでいう基底クラスとは、
**直接の親** を指します。

つまり通常継承では
「親は初期化リストで指定できるが、祖先は親が面倒を見る」
と考えてよいです。

ただし `ex03` の `virtual inheritance` だけは例外で、
仮想基底クラスは最終派生クラスが初期化します。
この module ではまず通常継承のルールを固めるのが優先です。

## コンストラクタは「上から下へ」呼ばれる

継承で最重要の挙動の 1 つです。

`ScavTrap serena("Serena");`

を作るとき、まず `ScavTrap` の中にある `ClapTrap` 部分を作らないと、
`ScavTrap` 全体は成立しません。

そのため生成順序は:

1. 基底クラス `ClapTrap`
2. 派生クラス `ScavTrap`

です。

破棄は逆順です。

1. 派生クラス `ScavTrap`
2. 基底クラス `ClapTrap`

### なぜ逆順なのか

派生クラスは基底クラスの上に乗っています。
作るときは土台から、壊すときは上から、というだけです。

sample のメッセージは、この順番を目で追えるようにしてあります。

### 初期化リストを書かなかったらどうなるか

派生クラスの初期化リストで基底クラスを明示しなかった場合、
基底クラスのデフォルトコンストラクタが自動で使われます。

つまり:

```cpp
ScavTrap::ScavTrap()
{
}
```

なら、まず `ClapTrap()` が呼ばれます。

ただしこれは
**基底クラスにデフォルトコンストラクタがあるときだけ** 成立します。

もし `ClapTrap()` が存在しないなら、
`ScavTrap` 側で `ClapTrap(name)` のように
明示的に指定しなければコンパイルできません。

## `ScavTrap` は何を「上書き」しているのか

`ScavTrap` では主に次を変えています。

- 初期ステータス
- コンストラクタ / デストラクタの表示メッセージ
- `attack()` の表示メッセージ
- `guardGate()` の追加

### ここでの `attack()` は virtual ではない

この sample では `attack()` を `virtual` にしていません。

理由は、この module で必要なのはまず

- 継承関係
- 同名関数の再定義
- `ScavTrap::attack()` を明示的に使うこと

を理解することだからです。

この段階では base class pointer を使った動的ディスパッチは出てきません。

ただし言葉としては、
厳密には「polymorphism のための override」というより、
**派生クラスで同名関数を再定義している**
と理解すると安全です。

## コピーコンストラクタで `ClapTrap(other)` と書ける理由

`ScavTrap` のコピーコンストラクタでは、
基底クラス部分も正しくコピーする必要があります。

そのため次のような形になります。

```cpp
ScavTrap::ScavTrap(const ScavTrap &other) : ClapTrap(other)
{
}
```

一見すると
「`ClapTrap` のコピーコンストラクタに `ScavTrap` を渡してよいのか」
と感じるかもしれません。

結論から言うと、これは問題ありません。

理由は `ScavTrap` が `ClapTrap` を継承しているため、
`ScavTrap` は `ClapTrap` として扱えるからです。

ここで起きているのは、
`other` の中にある **`ClapTrap` 部分を参照して**
新しい自分の基底クラス部分を作ることです。

つまり:

- `other` 全体を無理やり `ClapTrap` に変換しているわけではない
- `other` の基底クラス部分を使って、自分の基底クラス部分を構築している

と考えると分かりやすいです。

## スライシングとは何か

継承でよく出る注意点に
**object slicing（スライシング）** があります。

これは、派生クラスのオブジェクトを
基底クラスの **値** としてコピーしたときに、
派生クラス側の情報が切り落とされる現象です。

```cpp
ScavTrap s("Serena");
ClapTrap c = s;
```

このとき `c` に入るのは
`s` の中にある `ClapTrap` 部分だけです。

概念的には:

```text
ScavTrap
[ ClapTrap 部分 ][ ScavTrap 独自部分 ]

ClapTrap c = s;
[ ClapTrap 部分 ]
```

のようなイメージです。

### スライシングは違法ではない

これは C++ 的には合法です。

ただし多くの場合、
書いた人は「派生クラスとして扱いたい」と思っていたのに
うっかり値渡ししてしまい、
結果として基底クラス部分しか残らない、
というバグの原因になります。

そのため「避けるべきもの」として説明されることが多いです。

## 「基底クラスとして見るだけ」と「切り落としてコピーする」の違い

次の 2 つは見た目が似ていますが、本質が違います。

```cpp
ScavTrap s("Serena");
ClapTrap &ref = s;
```

これは **同じ実体を `ClapTrap` として見ているだけ** です。
新しいオブジェクトは作られていません。

一方、

```cpp
ScavTrap s("Serena");
ClapTrap c = s;
```

これは **新しい `ClapTrap` オブジェクトを作っている** ので、
`ScavTrap` 独自部分は落ちます。

したがって:

- 参照渡し `const ClapTrap &x` はスライシングしない
- 値渡し `ClapTrap x` はスライシングする

と覚えると実用的です。

### では `ClapTrap(other)` はスライシングなのか

`ScavTrap` のコピーコンストラクタの

```cpp
: ClapTrap(other)
```

は、嫌われる意味でのスライシングとは少し違います。

なぜなら目的が最初から
「新しい `ScavTrap` の中の `ClapTrap` 部分を構築すること」
だからです。

ここでは `ScavTrap` 全体を `ClapTrap` にして終わるのではなく、
**派生クラスの中にある基底クラスサブオブジェクトを初期化している**
だけです。

## `FragTrap` は `ScavTrap` と何が違うか

`FragTrap` も `ClapTrap` から派生しますが、
役割はかなり似ています。

違いは主に:

- 初期ステータスが違う
- 特殊能力が `highFivesGuys()` である
- attack の実装はそのまま `ClapTrap` を使ってもよい

です。

### ステータス一覧

| class | HP | Energy | Attack damage |
| --- | ---: | ---: | ---: |
| `ClapTrap` | 10 | 10 | 0 |
| `ScavTrap` | 100 | 50 | 20 |
| `FragTrap` | 100 | 100 | 30 |
| `DiamondTrap` | 100 | 50 | 30 |

この表は暗記するというより、
**どの親から何を引き継ぐのか**
を確認するために使ってください。

## 多重継承で何がまずいのか

`ex03` の `DiamondTrap` は

- `FragTrap`
- `ScavTrap`

の両方を継承します。

ここで何も考えずに書くと、
`DiamondTrap` の中に `ClapTrap` 部分が 2 つ入ります。

```text
DiamondTrap
|- ScavTrap
|  `- ClapTrap
`- FragTrap
   `- ClapTrap
```

これがいわゆる diamond problem です。

## `virtual inheritance` が必要な理由

この問題を避けるために sample では `ex03` で

```cpp
class ScavTrap : virtual public ClapTrap
{
};

class FragTrap : virtual public ClapTrap
{
};
```

としています。

これにより
`DiamondTrap` の中で `ClapTrap` は共有され、
**1 個だけ** 存在するようになります。

```text
DiamondTrap
|- ScavTrap
|- FragTrap
`- shared ClapTrap
```

subject の

> the ClapTrap instance of DiamondTrap will be created once, and only once

の意味はこれです。

## `DiamondTrap` の初期値はなぜ手で調整するのか

subject は `DiamondTrap` に対して:

- hit points は `FragTrap`
- energy points は `ScavTrap`
- attack damage は `FragTrap`

を要求しています。

しかし `ScavTrap` と `FragTrap` はそれぞれ自分の値をセットします。

そのため `DiamondTrap` のコンストラクタでは最後に明示的に

- `_hitPoints = 100`
- `_energyPoints = 50`
- `_attackDamage = 30`

とまとめ直すのが分かりやすい実装です。

## 名前が 2 つある理由

`DiamondTrap` には:

- `DiamondTrap` 自身の名前
- `ClapTrap` 部分の名前

の 2 種類があります。

subject では `ClapTrap` 側の名前に
`"_clap_name"` を付けるよう指定されています。

たとえば `DiamondTrap("Gemini")` なら:

- `DiamondTrap::_name` は `"Gemini"`
- `ClapTrap::_name` は `"Gemini_clap_name"`

です。

## 同じ名前のメンバ変数を持つと何が起こるか

subject は `DiamondTrap` の private 属性名を
`ClapTrap` の名前用メンバと同じ変数名にしろ、と要求しています。

つまり sample のように `ClapTrap` が `_name` なら、
`DiamondTrap` も `_name` を持ちます。

これは **name hiding（名前隠し）** を起こします。

`DiamondTrap` のメンバ関数内で単に `_name` と書くと、
`DiamondTrap::_name` を指します。

基底クラス側に触りたいなら:

```cpp
ClapTrap::_name
```

と明示しなければなりません。

これが `whoAmI()` の重要ポイントです。

## `attack()` はなぜ `ScavTrap::attack()` を呼ぶのか

subject には `DiamondTrap` の `attack()` は
`ScavTrap` 版を使うと書かれています。

したがって sample では:

```cpp
void DiamondTrap::attack(const std::string &target)
{
	ScavTrap::attack(target);
}
```

としています。

このように、
多重継承では **どの親の実装を採用するか明示する** ことがよくあります。

## 曖昧さが起きたら「どこから来た名前か」を書く

多重継承では同じ名前が複数の親から見えることがあります。

そのときは

- `ScavTrap::attack(target);`
- `ClapTrap::beRepaired(amount);`
- `ClapTrap::_name`

のように **スコープ解決演算子 `::`** で明示します。

これは C++ の重要な記法です。

## C++98 で気をつけること

この module では modern C++ の便利機能は使えません。

### 使わないもの

- `override`
- `final`
- `nullptr`
- range-based for
- `std::vector` などの STL コンテナ
- `<algorithm>`

### 書き方も古典的にする

- `NULL` か生ポインタを使う
- ループは普通の `for`
- Makefile は単純でよい

## subject 的によくある減点ポイント

- ヘッダに関数本体を書いてしまう
- include guard を忘れる
- `using namespace std;` を書く
- `friend` を使う
- `new` したのに `delete` しない
- コピーコンストラクタや代入演算子を省略する
- `DiamondTrap` で `ClapTrap` が 2 個できてしまう
- `DiamondTrap` の `attack()` が `ScavTrap` 版になっていない
- constructor / destructor の呼び順を理解しないまま書く

## sample コードの読み方

おすすめの順番は次です。

1. `ex00` の `ClapTrap` だけ読む
2. `ex01` で `ScavTrap` の差分だけ探す
3. `ex02` で `FragTrap` と `ScavTrap` の違いを見る
4. `ex03` で `virtual public` と `ClapTrap::_name` に注目する

特に `ex03` は
「継承したら便利」だけではなく、
**設計を間違えると曖昧さが増える**
ことを体感する exercise です。

## 最後に

Module 03 は、見た目はロボット遊びですが、
実際には C++ のクラス設計で非常に重要な基礎が詰まっています。

この module を通して最低限、自分の言葉で説明できるようにしたいのは:

- 継承とは何か
- `protected` はなぜ必要か
- constructor / destructor の順番はなぜそうなるか
- multiple inheritance の何が難しいか
- `virtual inheritance` は何を解決しているか

です。

ここが説明できるようになると、Module 04 以降の理解がかなり楽になります。
