# cpp_module02 lecture

## この lecture の目的

`cpp_module02` の subject は、見た目以上に複数の概念が同時に入っています。

- fixed-point number とは何か
- Orthodox Canonical Form は何のためにあるのか
- copy constructor と copy assignment operator は何が違うのか
- 演算子オーバーロードはどういう意味で実装するのか
- `const` メンバを持つクラスでは何が起こるのか
- 点が三角形の内部にあるかをどう判定するのか

この lecture は、sample コードを読むための補助というより、
上の問いに自分の言葉で答えられるようにするための読み物です。

## まず最初に: コンピュータは「実数そのもの」を持っていない

人間は `3.5` や `42.42` を「そのままの数」として見ます。
しかしコンピュータのメモリにあるのは最終的にはビット列です。

したがって「小数をどう表すか」は設計の問題です。

代表的には次の 3 種類があります。

### 1. 整数

`3`, `10`, `-42` のような値をそのまま整数として持ちます。

- 加算や比較が速い
- 小数を直接表せない

### 2. 浮動小数点数

`float` や `double` がこれです。
大きい値から小さい値まで広い範囲を表せますが、
「指数部」と「仮数部」を使うので、表現の仕組みが整数より複雑です。

- 広い範囲を表せる
- すべての小数を正確に表せるわけではない
- 演算結果に丸め誤差が入る

### 3. 固定小数点数

今回の主役です。
発想は単純で、

**「小数を含む値を、ある倍率で拡大して整数として保存する」**

という方法です。

これが subject の

> 「`2^fractionalBits` 倍した整数を持つ」

の意味です。

## fixed-point とは何か

### 基本の式

今回の `Fixed` クラスでは、内部に持つのは次の 2 つです。

```cpp
int _rawBits;
static const int _fractionalBits = 8;
```

ここで scale を

```text
scale = 2^fractionalBits = 2^8 = 256
```

とすると、
`Fixed` が表している本当の値は

```text
value = _rawBits / 256
```

です。

つまり `_rawBits` は「本当の値を 256 倍した整数」です。

### 具体例

| 表したい値 | 256倍した値 | 保存する `_rawBits` | 復元すると |
| --- | ---: | ---: | ---: |
| `0` | `0` | `0` | `0 / 256 = 0` |
| `1` | `256` | `256` | `256 / 256 = 1` |
| `0.5` | `128` | `128` | `128 / 256 = 0.5` |
| `3.5` | `896` | `896` | `896 / 256 = 3.5` |
| `-2.25` | `-576` | `-576` | `-576 / 256 = -2.25` |

この表の理解が、Module 02 の土台です。

### なぜこんなことをするのか

理由は「整数の世界で小数を扱いたいから」です。

たとえば `3.5` をそのまま整数では持てません。
でも 256 倍すれば `896` になり、整数として保存できます。

つまり fixed-point は:

- 保存するときは小数を拡大して整数化する
- 使うときは縮小して元の値として解釈する

というルールの上で成り立っています。

### なぜ `2^8` 倍なのか

`10` 倍でも `1000` 倍でもなく、なぜ `256` 倍なのか。

理由は 2 進数との相性です。

`2^8` 倍ということは、
2 進数で見れば「小数点の位置を 8bit 固定でずらしている」のと同じです。

```text
3.5 = 11.1(2)
8bit 固定小数点として持つイメージ
11.10000000(2)
```

これを「小数点を消した整数」として見ると、

```text
1110000000(2) = 896
```

になります。

厳密なビット図を毎回書ける必要はありませんが、

- fractional bits = 8
- 小数点の位置を 8bit 固定したまま整数として持つ

という感覚は重要です。

### fixed-point の長所と短所

長所:

- 比較や加減算が分かりやすい
- 浮動小数点より挙動を追いやすい
- 精度が「何bit小数部を持つか」で明確

短所:

- 表せる範囲は整数型の大きさに縛られる
- 小数部の精度は固定
- `0.1` のように、256 分の 1 で割り切れない値は誤差が出る

たとえば今回の最小単位は

```text
1 / 256 = 0.00390625
```

です。

したがって、`Fixed` が正確に表せる値は
`0.00390625` の整数倍だけです。

`42.42` はそのままでは表せないので、
一番近い値に丸めて保存されます。

## `_fractionalBits` が 8 で固定されている意味

`_fractionalBits` は各オブジェクトごとに違ってはいけません。

もしある `Fixed` が 8bit 小数部で、
別の `Fixed` が 5bit 小数部だったら、
同じ `_rawBits = 256` でも意味が変わってしまいます。

### 例

- 8bit 小数部なら `256 / 256 = 1.0`
- 5bit 小数部なら `256 / 32 = 8.0`

これでは比較も演算もできません。

だから今回のクラスでは

```cpp
static const int _fractionalBits = 8;
```

として、

- 全インスタンス共通
- 変更不可

にしてあります。

## Orthodox Canonical Form とは何か

Module 02 以降では、特別な指示がない限り、
クラスは Orthodox Canonical Form で書きます。

必要な 4 つは:

- default constructor
- copy constructor
- copy assignment operator
- destructor

です。

これは「オブジェクトの生成・コピー・破棄」を自分で明示的に扱う練習です。

## copy constructor と copy assignment operator は何が違うのか

ここは lecture の中でも最重要です。

### まず結論

- copy constructor は **新しいオブジェクトを作るとき** に使われる
- copy assignment operator は **すでに存在するオブジェクトへ代入するとき** に使われる

です。

### 1. copy constructor

```cpp
Fixed a;
Fixed b(a);
```

この `b` は、この行で初めて作られます。
まだ存在していなかった `b` を、
`a` をもとに初期化して作るのが copy constructor です。

別の書き方でも同じです。

```cpp
Fixed b = a;
```

これは代入に見えますが、
**宣言と同時の初期化** なので copy constructor です。

### 2. copy assignment operator

```cpp
Fixed a;
Fixed b;
b = a;
```

この `b` はすでに default constructor で作られています。
そのあとで `a` の内容を `b` に上書きするのが copy assignment operator です。

### 「生成」と「上書き」は別フェーズ

これを曖昧にすると C++ が読めなくなります。

- constructor: オブジェクトを作る
- assignment: すでにあるオブジェクトへ値を入れ直す

です。

人間の感覚で言えば:

- copy constructor は「新しいノートを 1 冊用意して、中身を書き写す」
- copy assignment は「すでにあるノートの内容を消して、別の内容を書き直す」

に近いです。

### なぜ区別が必要なのか

今の `Fixed` は `int` しか持っていないので差が見えにくいです。
しかし将来、クラスが

- ヒープメモリ
- ファイルハンドル
- ソケット

のような資源を持つと、
「新規生成時のコピー」と「既存オブジェクトへの上書き」では
やるべき処理が変わります。

だから C++ は最初からこの 2 つを分けています。

### sample の ex00 ではなぜ copy constructor の中で代入しているのか

`ex00` の sample では:

```cpp
Fixed::Fixed(const Fixed &other) : _rawBits(0)
{
    std::cout << "Copy constructor called" << std::endl;
    *this = other;
}
```

という形にしています。

これは:

- copy constructor が呼ばれた
- その内部で copy assignment operator を再利用した

ことを分かりやすく見るためです。

学習用としては有用ですが、
常にこの形が最良という意味ではありません。

今回の `Fixed` なら、より直接的には

```cpp
Fixed::Fixed(const Fixed &other) : _rawBits(other._rawBits)
{
}
```

でも十分です。

## ex00: まずは raw value を持つだけのクラス

### 何を学ぶ exercise か

`ex00` では fixed-point の演算はまだしません。
ここで学ぶのは主に:

- canonical form の 4 関数
- `getRawBits()` / `setRawBits()` の役割
- `const` メンバ関数

です。

### `getRawBits()` は何を返すのか

```cpp
int getRawBits(void) const;
```

これは「人間が見たい本当の値」ではなく、
**内部整数そのもの** を返します。

たとえば `3.5` を表す `Fixed` なら、
`getRawBits()` の結果は `3.5` ではなく `896` です。

### なぜ `const` が付くのか

```cpp
int getRawBits(void) const;
```

末尾の `const` は
「この関数はオブジェクトの状態を変更しない」
という約束です。

getter は基本的に読むだけなので `const` が自然です。

## ex01: 人間の値と内部整数を行き来する

ここから `Fixed` が「値として使えるクラス」になっていきます。

### int constructor

```cpp
Fixed::Fixed(const int value) : _rawBits(value << _fractionalBits)
{
}
```

`value << 8` は
`value * 256` と同じ意味です。

たとえば:

```text
10 << 8 = 2560
```

なので `10` を fixed-point にすると内部値は `2560` です。

### float constructor

```cpp
Fixed::Fixed(const float value)
    : _rawBits(static_cast<int>(roundf(value * 256)))
{
}
```

流れは:

1. `value` を 256 倍する
2. 一番近い整数に丸める
3. その整数を `_rawBits` に保存する

です。

### なぜ `roundf()` が必要なのか

たとえば `42.42f * 256 = 10859.52` です。

このとき単純に `static_cast<int>` すると、
`10859` へ切り捨てられます。

しかし fixed-point としては
`10860` の方が近いので、
`roundf()` で丸めてから整数化します。

### `toFloat()` と `toInt()`

内部値から人間が見たい値へ戻すには scale を逆に掛けます。

```cpp
float Fixed::toFloat(void) const
{
    return static_cast<float>(_rawBits) / 256.0f;
}
```

```cpp
int Fixed::toInt(void) const
{
    return _rawBits / 256;
}
```

### `toFloat()` で整数除算にしてはいけない理由

```cpp
return _rawBits / (1 << _fractionalBits);
```

とそのまま書くと、両方が整数なので整数除算になります。
つまり `896 / 256` は `3` になってしまい、
`3.5` の小数部分が消えます。

だから少なくとも片方を `float` にします。

### `toInt()` が「切り捨て」になる理由

`toInt()` は小数部を捨てて整数へ戻す関数です。
今回の sample では
右シフトより整数除算を使っています。

理由は、負数に対する右シフトの見え方を避けて、
学習者に「scale で割り戻している」と素直に伝えたいからです。

## `operator<<` はなぜ非メンバ関数なのか

subject では `std::cout << fixed` と書けるようにします。

### ここで左側にあるのは誰か

```cpp
std::cout << fixed;
```

この式で左側にいるのは `std::cout` です。
つまり「出力の主体」は `Fixed` ではなく `std::ostream` です。

したがって、自然な形は:

```cpp
std::ostream &operator<<(std::ostream &out, const Fixed &fixed);
```

です。

この関数は `Fixed` のメンバ関数ではなく、
`Fixed` を受け取る非メンバ関数です。

### `friend` を使わない理由

module の rules で `friend` は禁止です。
そこで sample では public な `toFloat()` を使って表示しています。

## ex02: `Fixed` を本当に数として振る舞わせる

### 比較演算子が raw 値だけで成立する理由

`Fixed` 同士は全員 scale が同じ 256 です。
だから:

```text
a > b
```

を判定するとき、
本当の値を毎回 `toFloat()` しなくても
`_rawBits` の大小比較で十分です。

### 例

- `3.5` の raw は `896`
- `2.0` の raw は `512`

`896 > 512` なので `3.5 > 2.0` です。

scale が共通だからこの比較が成立します。

### 加算と減算

scale が同じなら、加算と減算は raw 値同士でそのまま計算できます。

```cpp
result.setRawBits(_rawBits + other._rawBits);
```

#### 例

```text
3.5  -> 896
2.0  -> 512
合計 -> 1408
1408 / 256 = 5.5
```

### 乗算はなぜそのままではダメなのか

ここで scale が 2 重に掛かります。

`a = rawA / 256`, `b = rawB / 256` とすると:

```text
a * b = (rawA / 256) * (rawB / 256)
      = (rawA * rawB) / 65536
```

しかし new `Fixed` の raw 値として保存したいのは

```text
(a * b) * 256
```

です。

したがって:

```text
rawResult = (rawA * rawB) / 256
```

になります。

sample の実装:

```cpp
long product = static_cast<long>(_rawBits) * static_cast<long>(other._rawBits);
result.setRawBits(static_cast<int>(product / 256));
```

### なぜ `long` を使うのか

`int * int` は途中結果が大きくなりやすいです。
そのため、途中計算だけ少し広い型へ逃がしています。

これは「内部表現の幅」と「計算途中の幅」は別に考えるべき、という良い例です。

### 除算はなぜ先に左シフトするのか

除算は逆に、分子側の scale を先に増やしてから割ります。

```text
a / b = (rawA / 256) / (rawB / 256)
      = rawA / rawB
```

でも raw 値として保存したいのは
結果に `256` を掛けたものです。

だから:

```text
rawResult = (rawA * 256) / rawB
```

となります。

sample の実装:

```cpp
long dividend = static_cast<long>(_rawBits) << _fractionalBits;
result.setRawBits(static_cast<int>(dividend / other.getRawBits()));
```

## pre-increment と post-increment の違い

### 前置

```cpp
++a
```

は:

1. `a` を増やす
2. 増やした後の `a` 自身を返す

です。

だから戻り値は参照です。

```cpp
Fixed &operator++();
```

### 後置

```cpp
a++
```

は:

1. 増やす前の値をコピーして保存
2. `a` を増やす
3. 保存しておいた古い値を返す

です。

だから戻り値は値です。

```cpp
Fixed operator++(int);
```

### 1 回増やすとは何を意味するか

`_rawBits` を 1 増やすことは、
本当の値としては

```text
1 / 256 = 0.00390625
```

増えることです。

これが subject の言う
「最小表現単位」
です。

## `min` / `max` に const 版が必要な理由

```cpp
static Fixed &min(Fixed &lhs, Fixed &rhs);
static const Fixed &min(const Fixed &lhs, const Fixed &rhs);
```

ここでは 2 種類必要です。

### 非 const 版

変更可能なオブジェクトを受け取って、
変更可能な参照を返します。

### const 版

`const Fixed` を受け取れるようにする版です。

もし const 版がないと:

```cpp
const Fixed a(1);
const Fixed b(2);
Fixed::min(a, b);
```

が呼べません。

## ex03: `Point` と BSP

### `Point` が `const Fixed x; const Fixed y;` を持つ意味

`Point` は「作った後に座標を変えない点」として設計されています。

```cpp
class Point
{
  private:
    const Fixed _x;
    const Fixed _y;
};
```

これは immutability に近い設計です。

### なぜ初期化子リストが必要なのか

`const` メンバは、constructor の本体に入る前に初期化されていなければなりません。

だから:

```cpp
Point::Point(const float x, const float y) : _x(x), _y(y)
{
}
```

のように初期化子リストで書きます。

次のような書き方はできません。

```cpp
Point::Point(const float x, const float y)
{
    _x = Fixed(x); // const なので代入不可
    _y = Fixed(y);
}
```

## `Point` の copy assignment operator が awkward な理由

ここは subject の要求と C++ の型システムがぶつかっている箇所です。

### 問題

Orthodox Canonical Form を守るなら copy assignment operator を書きたい。
でも `Point` の座標は `const` なので、
一度作った後は再代入できません。

```cpp
Point a(1, 2);
Point b(3, 4);
a = b;
```

このとき `a._x = b._x;` は不可能です。

### sample の方針

sample では:

```cpp
Point &Point::operator=(const Point &other)
{
    (void)other;
    return *this;
}
```

という no-op にしています。

これは「意味のある代入」ができているわけではありません。
あくまで:

- subject が canonical form を要求している
- しかし `const` メンバ上、再代入はできない

という衝突の中で、
危険な抜け道を使わず安全側に倒した実装です。

### 評価時に説明できるようにすること

この部分は丸暗記ではなく、
次を説明できるようにしてください。

- copy assignment は「既存オブジェクトへの上書き」
- `const` メンバは上書きできない
- したがって `Point` は本質的には assignable な型ではない

ここを理解していれば、lecture の価値はあります。

## BSP は何を判定しているのか

### 目的

```cpp
bool bsp(Point const a, Point const b, Point const c, Point const point);
```

は「`point` が三角形 `abc` の内部にあるか」を判定します。

subject の条件では:

- 内部なら `true`
- 辺の上なら `false`
- 頂点の上でも `false`

です。

### 外積の符号を見る

3 点 `a`, `b`, `p` に対して、
辺 `ab` に対する `p` の位置は
2D 外積の符号で分かります。

```text
(b - a) x (p - a)
```

この値が:

- 正なら一方の側
- 負なら反対側
- 0 なら一直線上

です。

### 三角形に対してどう使うか

三角形の 3 辺に対して、

- `ab` と `point`
- `bc` と `point`
- `ca` と `point`

の符号を調べます。

内部にあるなら、`point` は 3 辺すべてに対して同じ向きにあります。

したがって:

- 正負が混ざったら外部
- 1 つでも 0 なら辺上または頂点上なので `false`
- 全部正、または全部負なら内部

です。

### 退化三角形

`a`, `b`, `c` が一直線上なら、そもそも三角形ではありません。
このとき面積に相当する外積が 0 になるので、
sample では最初に `false` を返しています。

## この module で特に押さえたい C++ の仕様

### 1. 宣言と実装を分ける

subject の rules にある通り、
template 以外の関数本体を header に書いてはいけません。

- `.hpp` には宣言
- `.cpp` には定義

を置きます。

### 2. include guard は必須

```cpp
#ifndef FIXED_HPP
#define FIXED_HPP
...
#endif
```

同じ header が複数回読まれても壊れないようにします。

### 3. `using namespace std;` は使わない

rules で禁止されています。

```cpp
std::cout
std::ostream
std::endl
```

のように毎回 `std::` を付けます。

### 4. `friend` を使わない

出力演算子は `friend` に頼らず、
public メンバ関数を通して実装します。

## よくあるミス

### fixed-point の本当の値を `_rawBits` そのものだと思ってしまう

`_rawBits` は本当の値ではありません。
本当の値は:

```text
_rawBits / 256
```

です。

### `toFloat()` で整数除算してしまう

小数部分が消えます。
必ず `float` にキャストするか `256.0f` で割ります。

### `operator*` と `operator/` の scale 補正を忘れる

加減算と同じ感覚で書くと壊れます。
掛け算と割り算だけは scale の再調整が必要です。

### `Fixed b = a;` を代入だと思ってしまう

これは見た目に反して copy constructor です。
宣言と同時なので「初期化」です。

### `Point` の `const` メンバへ代入しようとする

これは設計上できません。
constructor の初期化子リストで初期化する必要があります。

## sample コードを読むときの観点

### ex00

- constructor がいつ呼ばれるか
- assignment operator がいつ呼ばれるか
- `getRawBits()` は何を返しているか

を区別して見てください。

### ex01

- `10` がなぜ `2560` になるか
- `42.42f` に誤差が出るのはなぜか
- `toFloat()` / `toInt()` が何を戻すか

を式で追ってください。

### ex02

- 比較はなぜ raw 値だけでいいのか
- 乗除算でなぜ補正が必要か
- `++a` と `a++` の戻り値がなぜ違うか

を意識して読むと理解が深まります。

### ex03

- `Point` の `const` メンバが設計にどう影響するか
- BSP が「3 辺に対する向き判定」だと理解できるか

が重要です。

## 最後に

この module の本質は、
`Fixed` を 1 クラス実装すること自体ではありません。

本当に大事なのは次の 4 点です。

- 「値の表現方法」は自分で設計できる
- constructor と assignment は別の操作である
- 演算子オーバーロードは文法ではなく意味を実装する
- `const` はクラス設計そのものを制約する

この 4 点を理解していれば、Module 02 は先の module の土台になります。
