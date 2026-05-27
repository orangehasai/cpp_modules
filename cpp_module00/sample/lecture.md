# cpp_module00 lecture

## この lecture の目的

`cpp_module00` は課題の量自体は大きくありませんが、ここで出てくる文法と設計判断は今後の module 全体の前提になります。  
この資料では:

- 課題を解くための考え方
- C++98 の言語仕様として最低限理解しておきたいこと
- sample コードで実際に使っている書き方の意味

をまとめます。

この lecture は「答えの解説」ではなく、「なぜそのコードが C++ として自然なのか」を理解するための読み物です。

## まず押さえるべき前提

### C++ は C の上位互換ではあるが、書き方の発想はかなり違う

C では:

- `char *`
- `printf`
- 手動メモリ管理
- `struct` と関数を分けて書く

が中心でした。  
C++ では:

- `std::string`
- `std::cout`, `std::cin`
- クラス
- コンストラクタ
- `const`
- 参照
- 名前空間

が自然な道具になります。

課題文で `malloc/free` や `printf` が禁止されているのは、「C の書き方を C++ に移植する」のではなく、「C++ の道具で考える」ことを学ぶためです。

### C++98 を前提にする

この module では `-std=c++98` を付けても通る必要があります。  
つまり、現代 C++ でよく見る以下は使えません。

- `auto`
- range-based for
- `nullptr`
- lambda
- `std::to_string`
- move semantics

したがって、初学者としてはむしろ好都合です。  
便利機能が減るぶん、言語の基本構造を自分で理解しやすくなります。

## コンパイルモデルと翻訳単位

### ソースは 1 ファイルずつ別々にコンパイルされる

たとえば:

- `main.cpp`
- `PhoneBook.cpp`
- `Contact.cpp`

がある場合、コンパイラはまず各 `.cpp` を**それぞれ別の翻訳単位**として処理します。  
そのあと最後にリンクされます。

この性質のため、各 `.cpp` は:

- 自分が使う宣言を自分で見える状態にする
- 他の `.cpp` に依存して「たまたま見える」ことを期待しない

必要があります。

### ヘッダは「宣言を配るためのファイル」

ヘッダに書く主なもの:

- クラス宣言
- 関数宣言
- 定数宣言
- 型宣言

`.cpp` に書く主なもの:

- 関数本体
- メンバ関数本体
- `static` データメンバの定義

### 宣言と定義の違い

宣言は「こういう名前が存在します」という通知です。  
定義は「実体はこれです」です。

例:

```cpp
class PhoneBook;              // 宣言
void printLine(void);         // 宣言

void printLine(void)          // 定義
{
    std::cout << "line" << std::endl;
}
```

クラス定義そのものは多くの場合ヘッダに置きますが、**メンバ関数の本体はヘッダに置かない**のがこの課題のルールです。

## include と依存関係

### include は「ファイルをその場に展開する」に近い

```cpp
#include <string>
```

は感覚的には「`<string>` の中身をここに貼り付ける」に近い処理です。  
だから、同じヘッダを何度も読むと再定義事故が起きます。

### include guard

それを防ぐのが include guard です。

```cpp
#ifndef CONTACT_HPP
#define CONTACT_HPP

class Contact
{
};

#endif
```

### include what you use

使っている名前の宣言元ヘッダは、自分で include するのが原則です。

例えば:

- `std::string` を使うなら `<string>`
- `std::cout` を使うなら `<iostream>`
- `std::setw` を使うなら `<iomanip>`
- `std::istringstream` を使うなら `<sstream>`

今の環境では `<iostream>` が内部的に `string` 関連を引き込んでいて、`#include <string>` がなくても通る場合があります。  
しかしそれは実装依存なので、課題コードとしては頼らない方がよいです。

## 名前空間

### 名前空間は「名前の衝突を避けるための箱」

```cpp
namespace A
{
    void print(void);
}

namespace B
{
    void print(void);
}
```

この 2 つは同じ `print` という名前でも共存できます。

呼び出すときは:

```cpp
A::print();
B::print();
```

と書きます。

### 無名 namespace

名前を付けない namespace もあります。

```cpp
namespace
{
    std::string formatColumn(const std::string &text)
    {
        if (text.length() <= 10)
            return (text);
        return (text.substr(0, 9) + ".");
    }
}
```

これは**その翻訳単位の中でだけ見える名前**を作るための書き方です。  
`PhoneBook.cpp` の補助関数のように:

- ヘッダに公開したくない
- 他の `.cpp` から呼ばせたくない
- クラスメンバにするほどではない

という関数を閉じ込めるのに向いています。

ここでいう「同じファイル」は厳密には少し違い、正確には**同じ翻訳単位**です。  
つまり `.cpp` 本体だけでなく、そこに `#include` で展開された内容も含めて 1 単位として扱われます。

### 無名 namespace と `static` 関数

C 風に:

```cpp
static bool parseIndex(const std::string &input, int *index);
```

のように、ファイルスコープの関数へ `static` を付けて「この `.cpp` 限定」にする書き方もあります。  
C++ では無名 namespace でもほぼ同じ目的を達成できます。

無名 namespace の利点は、関数だけでなく:

- 定数
- 構造体
- クラス
- 補助型

もまとめてその翻訳単位限定にできることです。  
そのため C++ では、`.cpp` 専用の実装詳細を隠す手段として無名 namespace がよく使われます。

### ヘッダに無名 namespace を書くときの注意

無名 namespace は「include した先ごとに別物」ができます。  
そのため、基本的には `.hpp` ではなく `.cpp` に置く方が安全です。

### `std` とは何か

`std` は C++ 標準ライブラリの名前空間です。  
以下は全部 `std` の中にあります。

- `std::string`
- `std::cout`
- `std::cin`
- `std::endl`
- `std::setw`
- `std::istringstream`

### `::` はスコープ解決演算子

`A::print` は「`A` の中の `print`」という意味です。  
クラス名や名前空間名のあとに付いて、そのスコープに属する名前を指定します。

### `using namespace std;` を使わない理由

この課題では禁止です。  
理由は単にルールだからではなく、名前の衝突を防ぐ意図があります。

```cpp
std::cout << "Hello" << std::endl;
```

のように毎回 `std::` を明示した方が、

- どこに属する名前か分かる
- 衝突しにくい
- 大規模コードでも安全

という利点があります。

## 型・オブジェクト・値

### C++ では「型」が非常に重要

変数には必ず型があります。

```cpp
int number = 42;
char c = 'A';
std::string name = "Alice";
```

型が決まると:

- どれだけのメモリが必要か
- どんな演算ができるか
- どんな関数が呼べるか

が決まります。

### オブジェクト

C++ の文脈で「オブジェクト」は「メモリ上に実体を持つ値」と考えると入りやすいです。

```cpp
std::string name = "Bob";
```

この `name` は `std::string` 型のオブジェクトです。

### 初期化と代入は違う

```cpp
int a = 10;   // 初期化
a = 20;       // 代入
```

初期化は「作ると同時に値を与える」。  
代入は「すでに存在するオブジェクトに新しい値を入れる」。

この区別はクラスで重要になります。

## C文字列と `std::string`

### C文字列

```cpp
char text[] = "hello";
```

これは内部的には:

```cpp
{'h', 'e', 'l', 'l', 'o', '\0'}
```

のような配列です。  
末尾の `'\0'` が終端を表します。

### `char *` / `const char *`

```cpp
const char *p = "hello";
```

これは「文字列そのもの」ではなく、先頭文字のアドレスを保持するポインタです。

### `std::string`

```cpp
std::string s = "hello";
```

`std::string` はクラスであり、文字列の長さやメモリ管理を内部で扱います。  
使える操作も豊富です。

```cpp
s.length();
s.substr(1, 3);
s += " world";
```

### 使い分け

この module では、入力文字列や連絡先の保存にはほぼ `std::string` が自然です。  
ただし、`main(int argc, char **argv)` のように OS から渡される引数は C 形式なので、C文字列から C++ の文字列へ橋渡しする場面はあります。

## ポインタと参照

### ポインタ

```cpp
int x = 42;
int *p = &x;
```

`p` は `x` のアドレスを持っています。  
`*p` と書くと、そのアドレス先の値にアクセスします。

### 参照

```cpp
int x = 42;
int &r = x;
```

`r` は `x` の**別名**です。  
`r = 10;` は `x = 10;` と同じ意味です。

### `const std::string &text`

これは:

- `std::string`
- への参照
- ただし変更はしない

という意味です。

```cpp
void printName(const std::string &text);
```

この形の利点:

- コピーを避けられる
- 関数内で変更しないことを明示できる

### 値渡し / 参照渡し / const参照渡し

```cpp
void a(std::string text);          // コピーする
void b(std::string &text);         // コピーしない、変更できる
void c(const std::string &text);   // コピーしない、変更しない
```

読み取り専用の引数では `const T&` は非常によく使われます。

### 参照の実装と意味

言語仕様上、参照は「別名」です。  
実装上はコンパイラが内部でポインタのような仕組みを使うことがありますが、C++ のソース上では一貫して「別名」として扱われます。

つまり:

- `&r` は「参照そのものの住所」ではなく参照先の住所
- 参照は後から別の対象に付け替えられない
- 参照は `null` を通常の値として持たない

という性質があります。

## `const`

### `const` は「変更しない」という約束

```cpp
const int n = 42;
```

この `n` は変更できません。

### ポインタと `const`

```cpp
const char *p;
```

これは「`char` を変更しないポインタ」です。  
ポインタ変数 `p` 自体は別の場所を指すように変更できます。

### `const` メンバ関数

```cpp
int checkAmount(void) const;
```

末尾の `const` は、「このメンバ関数はオブジェクトの論理状態を変更しない」という意味です。

`Account` で:

- `checkAmount`
- `displayStatus`

に `const` を付けているのは、残高や状態を読むだけだからです。

### なぜ `const` が重要か

- 関数の意図が明確になる
- 間違った変更をコンパイラが防げる
- `const` オブジェクトにも呼べる

## クラス

### クラスは「データと操作をまとめた型」

```cpp
class Contact
{
public:
    void setName(const std::string &name);

private:
    std::string _name;
};
```

`Contact` は `std::string` と同じく、ユーザー定義型です。

### `public` と `private`

- `public`
  - クラスの外から使ってよい
- `private`
  - クラスの内側でだけ使う

これは単なる隠し方ではなく、「責務の境界」を作る仕組みです。

例えば `Contact` の名前データを外から直接いじらせず、

- セット方法
- 表示方法
- 妥当性チェック

をクラス側で管理できるようになります。

### メンバ関数

クラスの中で定義される関数をメンバ関数といいます。

```cpp
class Contact
{
public:
    void display(void) const;
};
```

本体は `.cpp` 側で:

```cpp
void Contact::display(void) const
{
    std::cout << "display" << std::endl;
}
```

と書きます。

`Contact::` は「この関数は `Contact` クラスに属する」という意味です。

### `this`

非 `static` メンバ関数の中では、暗黙的に `this` ポインタが存在します。  
これは「今操作しているオブジェクト自身」を指します。

```cpp
class Sample
{
public:
    void set(int value)
    {
        this->_value = value;
    }

private:
    int _value;
};
```

sample コードでは `this->` を多用していませんが、内部では同じ考え方で動いています。

## コンストラクタとデストラクタ

### コンストラクタ

オブジェクト生成時に呼ばれる特別な関数です。

```cpp
class Account
{
public:
    Account(int initial_deposit);
};
```

役割:

- メンバの初期化
- 作成時に必要な処理

### デストラクタ

オブジェクト破棄時に呼ばれる特別な関数です。

```cpp
~Account(void);
```

役割:

- 後片付け
- ログ出力
- 動的資源の解放

### 初期化リスト

```cpp
Account::Account(int initial_deposit)
    : _accountIndex(_nbAccounts), _amount(initial_deposit),
      _nbDeposits(0), _nbWithdrawals(0)
{
}
```

この `:` 以降が初期化リストです。  
代入ではなく、**メンバを最初からその値で構築する**ための構文です。

クラスメンバの初期化では、代入より初期化リストの方が本来の C++ の流儀に近いです。

## `static`

### クラスの `static` データメンバ

```cpp
class Account
{
private:
    static int _nbAccounts;
};
```

これは全 `Account` オブジェクトで共有される 1 個の変数です。

### `static` は「クラス共有」、`static const int` は「クラス内定数」

`static` が付くと、そのメンバは各オブジェクトの中に 1 個ずつ入るのではなく、クラス全体で 1 個だけ共有されます。

```cpp
class PhoneBook
{
private:
    static const int kMaxContacts = 8;
};
```

この `kMaxContacts` は「各 `PhoneBook` オブジェクトの状態」ではなく、「`PhoneBook` という型のルール」を表す値です。  
今回のように「最大 8 件」という上限は、個々のインスタンスごとに変わる性質の情報ではないので、`static const int` が自然です。

### なぜ `static const int` が固定長配列に使えるのか

C++98 では、固定長配列の長さには**コンパイル時に確定する整数定数**が必要です。

```cpp
class PhoneBook
{
private:
    static const int kMaxContacts = 8;
    Contact _contacts[kMaxContacts];
};
```

コンパイラはクラス定義を読んだ時点で:

- `kMaxContacts` は 8
- `_contacts` は `Contact` を 8 個持つ
- `sizeof(PhoneBook)` はこの大きさ

と確定できます。  
そのため、各インスタンスは生成時にメモリ確保されますが、**必要なサイズ自体はコンパイル時に決まっています**。

### `const` だけでは足りない理由

例えば次はダメです。

```cpp
class PhoneBook
{
private:
    const int _maxContacts;
    Contact _contacts[_maxContacts];
};
```

`_maxContacts` は `const` ですが、非 `static` メンバなので「各オブジェクトの一部」です。  
つまり値が意味を持つのはインスタンスごとであり、クラスのレイアウトを決める段階では使えません。

重要なのは:

- `const` は「変更できない」という意味
- `static const int` は「クラス共通で、配列長に使える整数定数」を作りやすい書き方

という違いです。

### 定義は `.cpp` に必要

ヘッダで宣言しただけでは実体はありません。  
どこか 1 箇所で定義が必要です。

```cpp
int Account::_nbAccounts = 0;
```

### `static` メンバ関数

```cpp
static void displayAccountsInfos(void);
```

これは特定オブジェクト 1 個ではなく、クラス全体に属する操作です。  
`this` を持たないので、非 `static` メンバには直接アクセスできません。

## スコープ

名前が有効な範囲をスコープといいます。

### ブロックスコープ

```cpp
if (true)
{
    int x = 10;
}
```

この `x` はブロックの外では使えません。

### クラススコープ

クラスメンバ名はそのクラスのスコープに属します。

### 名前空間スコープ

`std::cout` の `cout` は `std` 名前空間スコープに属します。

スコープを意識すると、同名変数や関数の混乱が減ります。

## 入出力ストリーム

### `std::cout`

標準出力ストリームです。

```cpp
std::cout << "Age: " << age << std::endl;
```

`<<` はストリーム挿入演算子と呼ばれ、左から右へ値を流し込みます。

### `std::cin`

標準入力ストリームです。

```cpp
std::cin >> number;
```

これは空白で区切って入力を読みます。

### `std::getline`

```cpp
std::string line;
std::getline(std::cin, line);
```

これは改行まで 1 行丸ごと読みます。  
空白を含む入力ではこちらが便利です。

### `std::endl`

```cpp
std::cout << std::endl;
```

これは:

- 改行
- flush

を行います。  
単なる改行だけなら `"\n"` もありますが、課題では `std::endl` の方が読みやすい場面も多いです。

### フォーマット用マニピュレータ

`std::setw(10)` は次の出力項目の表示幅を 10 にします。

```cpp
std::cout << std::setw(10) << text;
```

これは `SEARCH` の一覧表示で使います。

## 文字分類と `std::toupper`

### `std::toupper`

```cpp
std::toupper(ch);
```

は文字を大文字化する関数です。  
ただし安全に使うには、引数を `unsigned char` に変換してから渡すのが定石です。

```cpp
unsigned char current = static_cast<unsigned char>(text[i]);
result += static_cast<char>(std::toupper(current));
```

### `static_cast`

```cpp
static_cast<unsigned char>(text[i])
```

は「明示的に `unsigned char` に変換する」という意味です。  
C風キャストより意図が読みやすく、C++ ではこちらが推奨されます。

## 配列

### 固定長配列

```cpp
Contact _contacts[8];
```

これは `Contact` オブジェクトを 8 個並べた配列です。  
`PhoneBook` 課題では、最大件数が固定で動的確保禁止なので非常に相性がよいです。

`Contact _contacts[kMaxContacts];` のように書く場合も、結局は「`PhoneBook` 型は `Contact` を 8 個ぶん内蔵する型」として扱われます。  
したがって、`PhoneBook` オブジェクトを 1 個作るたびに `_contacts` の実体は一緒に確保されますが、その**配列長は実行時に変わりません**。

### 添字

```cpp
_contacts[0]
_contacts[1]
```

添字は 0 から始まります。  
範囲外アクセスは未定義動作です。

## ループと前置インクリメント

```cpp
for (int i = 0; i < 8; ++i)
{
}
```

`++i` は前置インクリメントです。  
`i++` は後置インクリメントです。

`int` では実用上ほぼ差はありませんが、C++ では:

- 「増やすだけ」の意図が明確
- iterator に対しても同じ癖で書ける

ため、`++i` を好む人が多いです。

## 暗黙変換と明示変換

### 暗黙変換

```cpp
std::string s = "hello";
```

これは `"hello"` から `std::string` への暗黙変換が起きています。

### 明示変換

```cpp
int n = static_cast<int>(3.14);
```

これは「変換する意思」をコード上に明示します。  
変換は便利ですが、意図しない情報損失も起こるので慎重に使います。

## 関数のオーバーロード

C++ では同じ名前の関数を引数違いで複数定義できます。

```cpp
void print(int n);
void print(const std::string &text);
```

これはオーバーロードです。  
module00 では自分で大量に書くことは少ないですが、標準ライブラリ側で多用されています。

## エラーと未定義動作

### コンパイルエラー

文法や型が間違っていて、そもそも実行ファイルが作れない状態です。

### 論理バグ

コンパイルは通るが、動作が間違っている状態です。

### 未定義動作

言語仕様が結果を保証しない危険な操作です。

例:

- 配列範囲外アクセス
- 不正なポインタ参照
- `std::toupper` に不正な値を渡す

未定義動作は「たまたま動く」ことがあるので、初心者ほど見落としやすいです。

## Makefile と警告オプション

### 課題の基本フラグ

```make
-Wall -Wextra -Werror -std=c++98
```

- `-Wall`
  - 基本的な警告を出す
- `-Wextra`
  - さらに多めの警告を出す
- `-Werror`
  - 警告をエラーとして扱う
- `-std=c++98`
  - C++98 としてコンパイルする

### `-pedantic`

これは課題必須ではありませんが、標準外拡張を炙り出すのに有用です。  
学習用にはかなり良いフラグです。

## exercise 00: Megaphone

### この exercise で見るべき言語仕様

- `main(int argc, char **argv)` の意味
- C文字列と `std::string` の橋渡し
- `std::toupper`
- ループ
- 文字単位アクセス

### `main` の引数

```cpp
int main(int argc, char **argv)
```

- `argc`
  - 引数の個数
- `argv`
  - 引数配列

`argv[i]` は 1 個の C文字列です。

### sample 実装の要点

`sample/ex00/megaphone.cpp` では、`argv[i]` を `std::string` 的に扱って 1 文字ずつ大文字化しています。  
ここで学ぶべきなのは、「OS からは C 形式で渡されるが、アプリケーション内部では C++ の型に寄せた方が扱いやすい」という発想です。

## exercise 01: My Awesome PhoneBook

### この exercise で見るべき言語仕様

- クラス定義
- アクセス制御
- 固定長配列
- メンバ関数
- `std::getline`
- `std::setw`
- `std::istringstream`

### `Contact` と `PhoneBook` を分ける意味

`Contact` は「1件の情報」という型です。  
`PhoneBook` は「複数件を管理する型」です。

これは単なるファイル分割ではなく、「役割ごとに型を分ける」という C++ の設計の基本です。

### 動的確保を使わない理由

課題ルールだから、だけではありません。  
まずは:

- オブジェクトを直接持つ
- 配列で持つ
- 所有関係を単純にする

という設計に慣れる意図があります。

### `SEARCH` の出力整形

この exercise は「クラス課題」に見えますが、実際には:

- 文字列操作
- 入力パース
- ストリーム整形

の練習にもなっています。

## exercise 02: The Job Of Your Dreams

### この exercise で見るべき言語仕様

- `static` データメンバ
- `static` メンバ関数
- コンストラクタ
- デストラクタ
- `const` メンバ関数
- 初期化リスト

### `Account` は「各口座」と「全体集計」を同時に持つ

個々の口座に属する状態:

- `_amount`
- `_nbDeposits`
- `_nbWithdrawals`
- `_accountIndex`

全口座で共有する状態:

- `_nbAccounts`
- `_totalAmount`
- `_totalNbDeposits`
- `_totalNbWithdrawals`

この「個別状態」と「共有状態」の分離が `static` の核心です。

### ログ出力が持つ意味

この exercise は単なる銀行口座課題ではなく、「オブジェクトのライフサイクルがどのタイミングで進むか」を観察する教材です。

つまり:

- 生成時に何が起こるか
- 入金時に何が起こるか
- 出金時に何が起こるか
- 破棄時に何が起こるか

をログで追えるようにしています。

## ヘッダを単体で使えるようにする

この課題群では特に重要です。  
例えば `Contact.hpp` が `std::string` を使っているなら、`Contact.hpp` 自身が `<string>` を include すべきです。

「先に別ファイルが include してくれているから動く」は不十分です。

## よくあるミス

- ヘッダに関数本体を書いてしまう
- `using namespace std;` を書く
- `std::string` を使っているのに `<string>` を直接 include しない
- `const` を付けるべき関数に付けない
- `static` データメンバの定義を `.cpp` に書き忘れる
- 配列範囲外アクセスをしてしまう
- `SEARCH` の幅 10 文字ルールを守らない
- 空欄をそのまま保存する
- `std::toupper` に `char` をそのまま渡してしまう

## sample コードの読み方

- `sample/ex00`
  - C文字列、`std::string`、文字変換、コマンドライン引数
- `sample/ex01`
  - クラス、メンバ関数、固定長配列、入力処理、書式整形
- `sample/ex02`
  - `static`、コンストラクタ、デストラクタ、初期化リスト、共有状態管理

コードを読むときは、「どう動くか」だけでなく次を確認すると理解が進みます。

- この型は誰が所有しているか
- この関数は値渡しか参照渡しか
- この名前はどのスコープに属するか
- この `const` は何を守っているか
- この include は何のために必要か

## 最後に

module00 の本質は、「C++ は C にクラスを足しただけではない」と体で覚えることです。  
この時点で以下を自然に説明できるようになると、その後かなり楽になります。

- `std::string` と `char *` の違い
- ポインタと参照の違い
- `const` の役割
- `public` / `private` の意味
- `static` が共有状態を表すこと
- ヘッダと `.cpp` を分ける理由
- `std::` を明示する理由

この module は小さくても、内容は軽くありません。  
分からない構文を「そういうもの」と流さず、1つずつ言語仕様として理解していくのが重要です。
