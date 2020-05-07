# 《Effective C++》学习笔记

## 0.让自己习惯C++

​     Accustoming Yourself to C++

- size_t只是一个unsigned int typedef；

- 每个函数的声明揭示其签名式，也就是参数和返回类型；

- 定义式是编译器为此对象拨发内存的地点；

- explicit阻止执行隐式（implicit）转换；

- copying 函数

  - copy构造函数：用来“以同型对象初始化自我对象”

    ```c
    Widget(const Widget& rhs);
    ```

  - copy assignment操作符：被用来“从另一个同型对象中拷贝其值到自我对象”

    ```c
    Widget& operator = (const Widget& rhs);
    ```

- 避免带有不明确行为的程序；

- 遵循一定的命名习惯：

  > lhs (left-hand-side),rhs(right-hand-side)
  >
  > pt(pointer to T)

## 1.视C++为一个语言联邦

- c++是多重范型编程语言，视c++包括4种次语言： 

  1：**C**:

  - 拥有区块（block），语句（statements），预处理（preprocessor），内置数据类型（built-in data types），数组（arrays），指针（pointer）等等。

  2：**Object-Oreinted C++**:

  - 弥补了C的诉求：classes,封装（encapsulation），继承（inheritance），多态（polymorphism），virtual等等。

  3：**Template C++**：

  - 增加了C++泛型编程（generic programming）部分，带来了TMP（模板元编程）。

  4：**STL**（template程序库，包括容器、迭代器、算法和函数对象）。

## 2.尽量以const，enum,inline替换 #define

​     Prefer const,enums,and inlines to #define.

- **原因：使用的名称可能未进入记号表（symbol table)**

- **我们无法利用#define创建一个class专属常量，因为#define不重视作用域(作用域在整个文件中)。一旦宏被定义，它就在其后的编译过程中有效。#define不能够用来定义class专属常量，也不能够提供任何封装性;但#include, #ifdef，#ifndef , #define, #endif仍有重要意义！**

- **const定义常量也可能比#define导致较少代码：因为#define仅仅由编译器盲目替换宏名称，可能会产生多份数据**

- **如果不想让一个pt or reference or handle指向某个整数常量，enum hack 十分有用，它比起const，更像#define：无法取得其地址**

  ```c++
  class GP{
      private:
      	enum {NumTurns = 5};
      	int scores[NumTurns];
      ...
  };
  struct CC{
      enum {NumTurns = 5};
  }
  ```

- **inline 函数可以替换#defines：既可以达到宏定义的效率，又可以避免不确定性错误！**

## 3.尽可能使用const

​     Use const whenever possible.

- 令函数返回一个常量值，可以预防无意义的赋值动作`if(a*b = c)`

- const成员函数：

  - **1.const对象只能访问const成员函数,而非const对象可以访问任意的成员函数** 

    ```c++
    const Widget A(lhs,rhs);//A is const object
    ...
    const Widger& operator*(const Widget& rhs)const;//const fc				
    ```
    
- **2.const成员函数不能修改对象的数据成员，const对象的成员变量不可以修改（mutable修饰的数据成员除外）**
  
- ![image-20200507151558894](C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20200507151558894.png)
  
- **两个成员函数如果只是常量性不同，是可以被重载的**
  
  ```c++
    const char& operator[](std::size_t position)const;
    char& operator[](std::size_t position);
    ```
  
- **当const和non-const成员函数有着实质等价的实现时，令non-const版本调用const版本避免代码重复,反之不能！**
  
  ```c++
    char& operator[](std::size_t position)
    {
        return 
            const_cast<char&>(
            	static_cast<const TB&>(*this)					[position]
        	);
    }
    ```

**注：**[C++强制类型转换](https://www.cnblogs.com/songhe364826110/p/11521589.html)

## 4.确定对象被使用前已经被初始化

​     Make sure that objects are initialized before they`re used.

- 为内置型对象进行手工初始化；内置类型以外，构造函数负责初始化责任

- 构造函数最好使用**成员初值列（效率高）** ，而不使用赋值操作 ：**构造赋值是伪初始化：1.系统为变量初始化 2.operator = 赋值**；最好总是以声明次序为其次序

- **不同编译单元的non-local static对象初始化相对次序并无明确定义**，以local对象替换non-local对象得以免除问题，例：

  ```c++
  class Example { ... };
  Example& emp()
  {
      static Example emp;//local static object
      return emp;
  }
  Example emp()
  {
  	Example emp;//local object
      return emp;
  }
  ```

- 函数内的local static对象会在“该函数调用期间”“首次遇上该对象之定义式”时被初始化

## 5.了解C++默默编写并调用哪些函数

Know what functions C++ silently writes and calls.

- 如果自己不声明， 编译器就会暗自为class创建一个default构造函数、一个copy构造函数、一个copy assignment操作符（代码合法有意义时编译器才会生成），以及一个析构函数
- base class如果把copy构造函数或copy assignment操作符设置为private，derived class将拒绝生成copy构造函数或copy assignment操作符

## 6.若不想使用编译器自动生成的函数，就该明确拒绝

Explicitly disallow the use of compile-generated functions you do not want.

- **将默认生成的成员函数声明为private而且故意不实现他们**，或者使用像**Uncopyable**这样的base class(依据是：基类声明coping函数为private则其派生类拒绝生成coping函数)
- ![image-20200507212838021](C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20200507212838021.png)

## 7.为多态基类声明virtual析构函数

Declare destructors virtual in polymorphic base classes.

- **polymorphic（带多态性质的）base classes才应该声明一个virtual析构函数**（免除“局部销毁”问题），不为多态用途的base classes不该声明virtual 析构函数

- Classes的设计如果不是为了做base classes使用，或者不是为了具备多态性，就不该声明virtual析构函数---浪费空间！

## 8.别让异常逃离析构函数

Prevent exceptions from leaving destructors.

- 析构函数绝对不能抛出异常；如果一个被析构函数调用的函数可能抛出异常，析构函数应该捕捉任何异常，然后吞下它们（不传播）或结束程序
- 如果客户需要对某个操作函数运行期间抛出的异常做出反应，那么类应该提供一个普通函数（而非在析构函数中）执行该操作
- <img src="C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20200507220609369.png" alt="image-20200507220609369" style="zoom: 80%;" />

- 因为析构函数吐出异常就是危险！带来“过早结束”或“不明确行为”的发生！

## 9.决不在构造和析构过程中调用virtual函数

Never call virtual functions during construction or destruction.

- **base class构造期间 virtual函数绝不会下降到derived classes阶层；**基类构造函数优先派生类被执行完成！
- base class构造或析构函数执行时derived class的成员变量尚未初始化，如果调用的virtual函数下降到derived class阶层，必定导致使用的成员变量未初始化 
- 在derived class的base class构造期间，对象的类型是base class，不会成为一个derived class对象
- ![image-20200507224329916](C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20200507224329916.png)
- **令次函数为static，也就不存在意外指向“初期未成熟的派生类对象内未被初始化的成员变量”**

## 10：令operator= 返回一个reference to *this

- 为了实现“连锁赋值”等
- 为operator*返回一个const reference to *this

