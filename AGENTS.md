## 概要
本プロジェクトはC++を通してOOPを学ぶ一連の42の課題です。cpp_modules課題は"cpp_module00"から"cpp_module09"まで存在し、moduleごとにディレクトリを作成します。

## あなたへの指示
課題内容が書かれているcpp_module*/docs/の.pdfを読み、課題内容に沿ってC++学習用のコードを初学者向けに作成してください。
コードはcpp_module*/sample/ex0*/に作成してください。またその課題で必要な知識、概念、コード記法、**言語特性/仕様**、注意点などをまとめた解説読み物をcpp_module*/sample/lecture.mdに作成してください。特に**記法、言語特性/仕様**などC++に関する知識はC言語エンジニア向けにメモリレベルまで細かく解説してください。

また全ての課題において以下に記載するルールを遵守する必要があります。

## コーディング規則/general rules

### Introduction
C++ is a general-purpose programming language created by Bjarne Stroustrup as an extension of the C programming language, or "C with Classes" (source: Wikipedia).

The goal of these modules is to introduce you to Object-Oriented Programming.
This will be the starting point of your C++ journey. Many languages are recommended for learning OOP. We decided to choose C++ since it’s derived from your old friend C.
Since C++ is a complex language, and in order to keep things simple, your code will follow the C++98 standard.
We are aware modern C++ is way different in a lot of aspects. So if you want to become a proficient C++ developer, it’s up to you to go further after the 42 CommonCore!
You will discover new concepts step-by-step. The exercises will progressively increase in complexity.

### General rules
#### Compiling
- Compile your code with c++ and the flags -Wall -Wextra -Werror
- Your code should still compile if you add the flag -std=c++98 -pedantic-errors
Formatting and naming conventions
- The exercise directories will be named this way: ex00, ex01, ... , exn
- Name your files, classes, functions, member functions and attributes as required in the guidelines.
- Write class names in UpperCamelCase format. Files containing class code will always be named according to the class name. For instance: ClassName.hpp/ClassName.h, ClassName.cpp, or ClassName.tpp. Then, if you have a header file containing the definition of a class "BrickWall" standing for a brick wall, its name will be BrickWall.hpp.
- Unless specified otherwise, every output message must end with a newline character and be displayed to the standard output.
- Goodbye Norminette! No coding style is enforced in the C++ modules. You can
follow your favorite one. But keep in mind that code your peer evaluators can’t understand is code they can’t grade. Do your best to write clean and readable code.
#### Allowed/Forbidden
You are not coding in C anymore. Time to C++! Therefore:
- You are allowed to use almost everything from the standard library. Thus, instead of sticking to what you already know, it would be smart to use the C++-ish versions of the C functions you are used to as much as possible.
- However, you can’t use any other external library. It means C++11 (and derived forms) and Boost libraries are forbidden. The following functions are forbidden too: *printf(), *alloc() and free(). If you use them, your grade will be 0 and that’s it.
• Note that unless explicitly stated otherwise, the using namespace <ns_name> and friend keywords are forbidden. Otherwise, your grade will be -42.
- You are allowed to use the STL only in Modules 08 and 09. That means:
no Containers (vector/list/map, and so forth) and no Algorithms (anything that requires including the <algorithm> header) until then. Otherwise, your grade will be -42.
#### A few design requirements
- Memory leakage occurs in C++ too. When you allocate memory (by using the new keyword), you must avoid memory leaks.
- From Module 02 to Module 09, your classes must be designed in the Orthodox
Canonical Form, except when explicitly stated otherwise.
- The "From now on" rule introduced in Module 02 is a continuing rule for all
later modules as well. Therefore, when working on Modules 03 to 09, assume the
Orthodox Canonical Form is still required unless that module or exercise
explicitly states otherwise. In practice, this means classes should provide the
default constructor, copy constructor, copy assignment operator, and
destructor.
- Any function implementation put in a header file (except for function templates) means 0 to the exercise.
- You should be able to use each of your headers independently from others. Thus, they must include all the dependencies they need. However, you must avoid the problem of double inclusion by adding include guards. Otherwise, your grade will be 0.
#### Read me
- You can add some additional files if you need to (i.e., to split your code). As these assignments are not verified by a program, feel free to do so as long as you turn in the mandatory files.
- Sometimes, the guidelines of an exercise look short but the examples can show requirements that are not explicitly written in the instructions.
- Read each module completely before starting! Really, do it.
- By Odin, by Thor! Use your brain!!!


