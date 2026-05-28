# cpp_module01 lecture

## この lecture の目的

`cpp_module01` は、`cpp_module00` で触れたクラスの基本に対して、

- オブジェクトをどこに確保するか
- ポインタと参照をどう使い分けるか
- 文字列処理とファイル入出力をどう組み合わせるか
- メンバ関数ポインタや `switch` をどう読むか

を追加で学ぶ module です。

この資料は sample コードを読むための補助であり、単なる答え合わせではなく
「なぜその書き方が必要なのか」を理解するための読み物として使ってください。

## module01 の中心テーマ

### 1. スタックとヒープの違いを体で覚える

`ex00` と `ex01` の本質は、Zombie を作ること自体ではありません。  
本当に見てほしいのは:

- ローカル変数として作るオブジェクトは、スコープを抜けると自動で破棄される
- `new` で確保したオブジェクトは、自分で `delete` するまで生き続ける
- 配列を `new[]` したら、対応する解放は `delete[]` である

という寿命管理です。

### 2. 参照は「別名」、ポインタは「アドレスを保持する変数」

`ex02` と `ex03` では、この違いが設計に直結します。

- 参照は必ず何かを参照していなければならない
- 参照は後から別の対象に付け替えられない
- ポインタは `0` を入れて「まだ何も指していない」を表現できる
- ポインタは後から別の対象を指すように変更できる

この差があるので:

- `HumanA` は常に武器を持つので `Weapon &`
- `HumanB` は武器なしの状態があり得るので `Weapon *`

という設計になります。

### 3. C++ の文字列とストリームに慣れる

`ex04` では C の `fopen` / `fread` / `fwrite` ではなく、

- `std::ifstream`
- `std::ofstream`
- `std::string`
- `find`
- `substr`

を使って「C++ 的にファイルを書き換える」練習をします。

### 4. 制御構文と少し癖のある型に慣れる

`ex05` と `ex06` では:

- メンバ関数ポインタ
- `switch`
- `switch` の fallthrough

が出てきます。  
文法が少し読みにくいので、ここで一度整理しておく価値があります。

## オブジェクトの寿命

### スタック上のオブジェクト

```cpp
void randomChump(const std::string &name)
{
    Zombie zombie(name);
    zombie.announce();
}
```

この `zombie` は関数を抜けると自動で破棄されます。  
そのため:

- 使い捨ての短い寿命
- 関数の外に持ち出さない

場合に向いています。

### ヒープ上のオブジェクト

```cpp
Zombie *newZombie(const std::string &name)
{
    return new Zombie(name);
}
```

こちらは関数を抜けても消えません。  
代わりに呼び出し側が:

```cpp
Zombie *z = newZombie("Heapy");
delete z;
```

のように明示的に解放する必要があります。

### `new` と `delete` は必ず対応させる

- `new X` に対して `delete`
- `new X[n]` に対して `delete[]`

を使います。  
ここを間違えると未定義動作です。

### `ex01` で default constructor が必要になりやすい理由

```cpp
Zombie *horde = new Zombie[N];
```

と書くと、配列の各要素はまず default constructor で作られます。  
そのあとで `setName()` のようなメンバ関数を使って名前を入れるのが
最も素直な実装です。

## destructor は「後始末の場所」

この module では destructor に

- デバッグ表示
- 将来メモリやファイルを持つようになったときの後始末

という意味があります。

`ex00` と `ex01` で destructor メッセージを出すと:

- スタックの Zombie はいつ死ぬか
- `delete` / `delete[]` の瞬間に何が起きるか

が目で追えます。

## ポインタと参照

### `ex02` で確認したいこと

```cpp
std::string brain = "HI THIS IS BRAIN";
std::string *stringPTR = &brain;
std::string &stringREF = brain;
```

ここで重要なのは:

- `stringPTR` は「アドレスを格納した変数」
- `stringREF` は「brain の別名」

という点です。

そのため:

- `stringPTR` の中身は `&brain`
- `&stringREF` も `&brain`
- `*stringPTR` と `stringREF` はどちらも同じ文字列を読む

となります。

### 参照の特徴

- 宣言時に初期化が必要
- `NULL` のような「何も参照しない状態」を作れない
- 一度結び付いたら参照先を変えられない

### ポインタの特徴

- `0` を入れて未接続状態を表現できる
- 後から別の対象を指せる
- `*ptr` や `ptr->member` のように明示的な参照外しが必要

## `ex03` の設計判断

### `Weapon::getType()` が `const std::string &` を返す理由

```cpp
const std::string &getType(void) const;
```

これには 2 つ意味があります。

1. `std::string` を毎回コピーしない
2. 呼び出し側に「この戻り値を書き換えないでほしい」と伝える

### `HumanA` は参照を持つ

```cpp
HumanA(const std::string &name, Weapon &weapon);
```

`HumanA` はコンストラクタ時点で武器を受け取り、その後ずっと武器ありです。  
この条件なら参照が自然です。

### `HumanB` はポインタを持つ

```cpp
Weapon *weapon;
```

`HumanB` は最初は武器なしでもよいので、`weapon` を `0` にしておけます。  
あとから `setWeapon()` で接続できる点も要件に合っています。

## 文字列置換の考え方

### `std::string::replace` 禁止の意味

`ex04` は「便利関数を呼ぶだけ」で終わらせず、

- どこで一致したかを `find()` で探す
- 前半を `substr()` で切り出す
- 置換後の文字列を自分で組み立てる

流れを理解するための exercise です。

### 典型的な実装パターン

```cpp
start = 0;
found = content.find(s1, start);
while (found != std::string::npos)
{
    result += content.substr(start, found - start);
    result += s2;
    start = found + s1.length();
    found = content.find(s1, start);
}
result += content.substr(start);
```

これは:

1. 一致位置までの未処理部分を result に追加
2. `s1` の代わりに `s2` を追加
3. 次の探索開始位置を更新

という手順です。

### `s1` が空文字のときは特別扱いが必要

空文字はどこにでも一致してしまいます。  
そのままループすると無限ループになり得るので、先に弾くのが安全です。

## メンバ関数ポインタ

### `ex05` の文法

```cpp
typedef void (Harl::*ComplaintHandler)(void);
```

これは「`Harl` クラスのメンバ関数を指すポインタ型」です。  
普通の関数ポインタより少し特殊で、呼び出すときにオブジェクトが必要です。

```cpp
(this->*handlers[i])();
```

この書き方は:

- `handlers[i]` が指しているメンバ関数を
- `this` という現在のオブジェクトに対して
- 呼び出す

という意味です。

### なぜ `if / else if` の森を避けるのか

課題文は「member function pointer を使え」と言っています。  
つまり `ex05` の主題は:

- 文字列と処理を対応付ける
- 関数も値として扱う

ことです。

## `switch` と fallthrough

### `ex06` で見たいこと

`WARNING` が来たら:

- `WARNING`
- `ERROR`

の順に表示したいので、`switch` の fallthrough が便利です。

```cpp
switch (levelIndex(level))
{
    case 0:
        debug();
    case 1:
        info();
    case 2:
        warning();
    case 3:
        error();
        break;
    default:
        std::cout << "[ Probably complaining about insignificant problems ]"
                  << std::endl;
}
```

`break` を途中に置かないことで、マッチした case から下へ処理が流れます。  
これを fallthrough と呼びます。

### `switch` は整数型に対して使う

C++98 の `switch` は文字列へ直接は使えません。  
そのため sample ではまず:

- `"DEBUG"` なら `0`
- `"INFO"` なら `1`
- `"WARNING"` なら `2`
- `"ERROR"` なら `3`

という変換をしてから `switch` しています。

## C++98 で気を付けること

この module でも modern C++ の書き方は使いません。

- `nullptr` ではなく `0` または `NULL`
- range-based for は使えない
- `auto` は使えない
- `std::to_string` は使えない

そのため、型を明示して素直に書くのが基本です。

## よくあるミス

### `ex00` / `ex01`

- `new` したのに `delete` しない
- `new[]` に対して `delete` を使ってしまう
- 配列要素へ名前を入れ忘れる

### `ex02`

- 参照の値を表示するときに `*stringREF` と書こうとしてしまう
- `stringREF` 自体はもう値なので `*` は不要

### `ex03`

- `HumanA` の参照メンバをコンストラクタ初期化子で初期化していない
- `HumanB` の `weapon` が `0` の可能性を考えずに `weapon->getType()` してしまう

### `ex04`

- `s1` が空文字でも置換処理を始めてしまう
- 読み込み失敗と空ファイルを区別していない
- 1 行ずつ処理した結果、末尾改行の扱いを壊してしまう

### `ex05`

- 普通の関数ポインタとメンバ関数ポインタを同じだと思ってしまう
- `(this->*ptr)()` の形を忘れる

### `ex06`

- `switch` に `std::string` を直接入れようとしてしまう
- fallthrough を理解せず途中で `break` してしまう

## sample コードの見方

各 `sample/ex0*` は:

- 課題の提出ファイル構成に近い形
- `main.cpp` で最低限の確認ができる形
- C++98 と課題ルールに合わせた形

で作ってあります。

まずは:

1. `Makefile` を読む
2. `.hpp` で宣言を見る
3. `.cpp` で実装を見る
4. `main.cpp` で使い方を見る

の順で追うと理解しやすいです。

## 最後に

`cpp_module01` は文法量よりも、「寿命」と「所有者」を意識し始める module です。  
誰がオブジェクトを作り、誰が破棄し、今そのオブジェクトは存在してよいのかを
常に考える癖を付けてください。  
この感覚は `cpp_module02` 以降でもずっと必要になります。
