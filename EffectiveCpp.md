# :triangular_flag_on_post:《Effective C++》学习笔记 

:runner:记录生活，热爱生活！

[toc] 

---------------

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
  
- <img src="https://raw.githubusercontent.com/Super-DoXCDH/learngit/master/images/image-20200507151558894.png" alt="image-20200507151558894" style="zoom:80%;" />
  
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
            	static_cast<const TB&>(*this)[position]
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
- <img src="https://raw.githubusercontent.com/Super-DoXCDH/learngit/master/images/image-20200507212838021.png" alt="image-20200507212838021" style="zoom:80%;" />



## 7.为多态基类声明virtual析构函数

Declare destructors virtual in polymorphic base classes.

- **polymorphic（带多态性质的）base classes才应该声明一个virtual析构函数**（免除“局部销毁”问题），不为多态用途的base classes不该声明virtual 析构函数

- Classes的设计如果不是为了做base classes使用，或者不是为了具备多态性，就不该声明virtual析构函数---浪费空间！



## 8.别让异常逃离析构函数

Prevent exceptions from leaving destructors.

- 析构函数绝对不能抛出异常；如果一个被析构函数调用的函数可能抛出异常，析构函数应该捕捉任何异常，然后吞下它们（不传播）或结束程序
- 如果客户需要对某个操作函数运行期间抛出的异常做出反应，那么类应该提供一个普通函数（而非在析构函数中）执行该操作
- <img src="https://raw.githubusercontent.com/Super-DoXCDH/learngit/master/images/image-20200507220609369.png" alt="image-20200507220609369" style="zoom: 80%;" />
- 
- 因为析构函数吐出异常就是危险！带来“过早结束”或“不明确行为”的发生！



## 9.决不在构造和析构过程中调用virtual函数

Never call virtual functions during construction or destruction.

- **base class构造期间 virtual函数绝不会下降到derived classes阶层；**基类构造函数优先派生类被执行完成！
- base class构造或析构函数执行时derived class的成员变量尚未初始化，如果调用的virtual函数下降到derived class阶层，必定导致使用的成员变量未初始化 
- 在derived class的base class构造期间，对象的类型是base class，不会成为一个derived class对象
- <img src="https://raw.githubusercontent.com/Super-DoXCDH/learngit/master/images/image-20200507224329916.png" alt="image-20200507224329916" style="zoom:80%;" />
- **令次函数为static，也就不存在意外指向“初期未成熟的派生类对象内未被初始化的成员变量”**



## 10.令operator= 返回一个reference to *this

- 为了实现“连锁赋值”等
- 为operator*返回一个const reference to *this [防止a * b =c]



## 11.在operator= 中处理“自我赋值”

Handle assignment to  self in operator=.

- 加一个“证同测试”使具有“自我赋值安全性”
  精心安排的语句可以使代码具有“异常安全性”（自动获得“自我赋值安全性”）：在复制构造之前别删除原指针

  ```c++
  if (this == &rhs) return *this;//别用*this == rhs，效率太低！
  ```

- 另一种替代方案是“copy and swap”技术

  ```c++
  Widget& Widget::operator=(const Widget& rhs)
  {
      Widget temp(rhs);
      swap(temp);
      return *this;
  }
  ```

- 注：**将copying动作从函数本体移至函数参数构造阶段牺牲了清晰性，有时却可生成更高效的代码**

  ```c++
  Widget& Widget::operator=(Widget rhs)
  {
      swap(rhs);
      return *this;
  }
  ```



## 12.复制对象时勿忘其每一个成分

Copy all parts of an object.

- 复制所有的local成员变量以及所有base class成分

  ```c++
  Derived::Derived(param):Base(param),data_D(param){}
  
  Derived& Derived::operator=(const Derived& rhs) 
  {
      Base::operator=(rhs);
      ...//派生类的赋值
      return *this;
  }
  ```

- 不要尝试以一个copying函数实现另一个copying函数。应将共同机能放进第三个函数中并由它们共同调用



## 13.以对象管理资源

Use objects to manage resources.

**为了防止资源泄漏，请使用RAII对象，在构造函数里面获得资源，并在析构函数里面释放资源** 

- [x] 下面都是“类指针对象”：重载了有指针行为的函数

- **auto_ptr**：被销毁会自动删除它所指之物，复制所得的指针将获得资源的唯一拥有权，可以控制权移交
- scoped_ptr:防拷贝指针
- shared_ptr:引用计数指针
- weak_ptr:弱指针与shared_ptr类似，不同点是不能修改资源引用技术，也就是没有资源管理权,
  - 用来辅组shared_ptr解决循环引用问题！
- **引用计数型智慧指针（RCSP）**：持续追踪多少个指针指向该资源，无人指向他时自动删除该资源

```c++
#include<memory>
std::shared_ptr<T> ptr(new T(init_param));
```



**注：**<img src="https://raw.githubusercontent.com/Super-DoXCDH/learngit/master/images/image-20200508185023724.png" alt="image-20200508185023724" style="zoom:80%;" />



## 14.在资源管理类中小心coping行为

Think carefully about copying behavior in resource-managing classes.

一般资源管理类复制时可以选择以下做法： 

- 禁止复制（复制不合理）private inheritance Uncopyable or set coping fc private
- “引用计数法”（使用tr1::shared_ptr指定“删除器”阻止引用次数为0时的删除行为）
- 复制底层资源（“深度拷贝”）
- 转移底部资源的拥有权（auto_ptr）



## 15.在资源管理类中提供对原始资源的访问

Provide access to raw resources in resource-managing classes.

- get成员函数实现**显式转换**（安全，受欢迎）

  ```C++
  T* get() const {return this->ptr;}
  ```

- **隐式转换函数**operator算子（方便）：

  ```c++
  class Tmp{
  public:
      ...
      operator TmpConvertType() const  //隐式转换函数
      { return t; }
      ...
  private:
      TmpConvertType t;
  };
  ...
  Tmp f1;
  Tmp f2 = f1;//此处会用operator算子执行隐式转换，返回f1的t给f2的copy构造函数
  //operator算子的隐式类型转换，使用-当前对象去生成另一个类型的对象-（正好与构造函数型相反），这种转换必须有operator算子的支持。
  ```



## 16.成对使用new和delete时要采用相同形式

Use the same form in corresponding uses of new and delete.

- new和delete对应，new[ ]和delete[ ]对应

**注：**[new与malloc的区别](https://www.cnblogs.com/shilinnpu/p/8945637.html)



## 17.以独立语句将newed对象置于智能指针

Store newed objects in smart pointers in standalone statements.

- 如果不这样做，一旦抛出异常，有可能导致难以察觉的资源泄漏

```c++
processWidget(std::shared_ptr<Widget> pw, int priority);
...
processWidget(std::shared_ptr<Widget>(new Widget(param)),priority());
//不支持隐式构造，所以第一个参数不能是new Widget
//执行顺序有很大弹性！容易造成内存泄漏
//推荐以下写法
std::shared_ptr<Widget> pw(new Widget(param));
processWidget(pw,priority());
```

## 18.让接口容易被正确使用，不易被误用

Make interfaces easy to use correctly and hard to use incorrectly.

- 好的接口很容易被正确使用，不容易被误用；努力达成这些性质

- 促进正确使用”的办法包括接口的一致性，以及与内置类型的行为兼容

- “防治误用”的办法包括建立新类型，限制类型上的操作，束缚对象值，以及消除用户的资源管理责任

- tr1::shared_ptr支持定制型删除器，可预防DLL问题，可被用来自动解除互斥锁等等 

     

## 19.设计class犹如设计type

Treat class design as type design.

- 好的types有自然的语法，直观的语义，以及一或多个高效实现品，设计时考虑所面对的问题

  - 新type的对象应该如何被创建和销毁？

  - 对象的初始化和赋值该有怎样的差别？

  - 新type的对象如果被passed by value，意味着什么？

  - 新type的合法值？

  - 新type需要配合某个继承图系吗？

  - **新的type需要什么样的转换-允许T1->T2（types）要么声明non-explicit-one-argument或者是写一个operator T2转换函数；如果是explicit构造，那么只能声明一个不能执行上述转换的函数**，explicit关键字，阻止“以赋值语法进行带有转型操作的初始化”

    - **对于non-explicit-one-argument type!**

    - Widget a(param);//调用构造函数,**推荐**
    - Widget c = param;//调用构造函数,**不推荐**写法
    - [ ] Widget b = a;//调用copy assignment构造,**不推荐**写法
    - [x] Widget b;b=a;//调用copy assignment构造,**推荐**
    - Widget b(a);//调用copy构造

  - 什么样的操作符和函数对此type而言是合理的？

  - 什么样的函数应该驳回？private者！

  - 新的成员的类型如何？  

  - 什么是新type”未声明接口“？

  - 新type的一般化程度？

  - 是否需要新type？

## 20.习惯pass-by-reference-to-const替换pass-by-value以提高效率

Prefer to pass-by-reference-to-const to pass-by-value.

- 尽量以pass-by-reference-to-const替换pass-by-value，比较高效（减少了匿名对象的构造析构），并可避免切割问题

- 对象切割发生在public继承（is-a）以派生类给基类赋值时！

- 对于**内置类型**，以及STL的迭代器和函数对象pass-by-value往往更高效

  

## 21.必须返回对象时，别妄想返回其reference

Don`t try to return a reference when you must return an object.

- 绝不要返回pointer或reference指向一个local stack对象（在函数退出前被销毁）

- 不要返回pointer或reference指向一个heap对象（**用户**不知道如何delete,或者说不知道返回了heap对象）

- 不要返回pointer或者reference指向local static对象而有可能需要多个这样的对象（同一行不能调用多次该函数，static只有一份）

  ```c++
  const Rational& operator*(const Rational& lhs, const Rational& rhs)
  {
      static Rational result;
      result = ...;
      return result;
  }
  ...
  Rational a,b,c;
  if((a*b) == (b*c));//该判断永远为真，static的引用总返回”现值“
  ```

  

## 22.将成员变量声明为private

Declare data members private.

- 切记将成员变量申明为private，**通过函数实现”不准访问“，“只读访问”，“读写访问”**，这可具有语法的一致性、更精确的访问控制、封装、提供class作者充分的实现弹性等优点
- **protected并不比public更有封装性**，一样不具备良好的封装性，在继承过程中！



## 23.推荐non-member,non-friend替换member函数

Prefer non-member,non-friend functions to member functions.

- 愈多函数可访问它，数据的封装性就愈低，故member函数封装性差
- 将所有便利函数放在多个头文件内但隶属同一个命名空间（**namespace可跨多个头文件编译**），意味客户可以轻松扩展这一组便利函数，降低了编译相依度，这正是STL的做法

![image-20200509161118789](https://raw.githubusercontent.com/Super-DoXCDH/learngit/master/images/image-20200510142814346.png)



## 24.若所有参数需类型转换，请为此采用non-member函数

Declare non-member functions when type conversions should apply to all parameters.

- 只有当参数被列于参数列内，这个参数才是隐式类型转换的合格参与者；**this对象**（隐喻参数）绝不是隐式类型转换的合格参与者
- menber函数的反面是non-member函数，不是friend函数
- **non-member函数，允许编译器在每一个实参上执行隐式类型转换**



## 25.考虑写出一个不抛出异常的swap函数(:sos:)

Consider support for a non-throwing swap.

- 当std::swap对自定义类型效率不高时(例如深拷贝)，提供一个swap成员函数，并确定不会抛出异常

  ```c++
  void swap(T* lhs, T* rhs)
  {
      using std::swap;
      swap(lhs,rhs);
  }
  ```

- 当要对C++模板偏特化时（当然C++并不支持），可以间接通过提供一个member swap，再提供一个non-member swap用来调用前者 

  ```c++
  namespace Widget {
  	template<typename T>
  	void swap(Widget<T> lhs, Widget<T> rhs)
  	{
  	    lhs.swap(rhs);//调用Widget类成员函数！
  	}
  }
  ```

  

- 为“用户定义类型”进行std templates全特化是好的，但千万不要尝试在std内加入某些对std而言全新的东西

**注：不可以添加新的东西到std内，调用swap时应该针对std::swap使用using声明式，然后调用swap不带任何”命名空间修饰”**

```c++
void doSomething(T& obj1, T& obj2)
{
    ...
    using std::swap;//推荐写法，为T类型调用最佳swap版本；std::swap(obj1,obj2)无法保证这点
    swap(obj1,obj2);
    ...
}
```



## 26.尽可能延后定义式的出现时间

Postpone variable definitions as long as possible.

- 不只应该延后变量定义直到非得使用该变量的前一刻为止，甚至**应该尝试延后这份定义直到能够给它初值实参为止**(***接口类，句柄类***)，这样可增加程序的清晰度并改善程序效率

![image-20200510142814346](https://raw.githubusercontent.com/Super-DoXCDH/learngit/master/images/image-20200509161118789.png)



- A: 1个构造，1个析构，n次赋值
- B: n次构造，n次析构

- **A大多时候更高效，但还是以情况而论**



## 27.尽可能少做转型动作

Minimize casting.

- 如果可以，尽量避免转型---**转型破坏了类型系统**，特别是在注重效率的代码中避免dynamic_cast(代价太高）；试着发展无需转型的替代设计
- 如果转型是必要的，试着将它隐藏于某个函数后
- 宁可使用**C++-style转型**，不要使用**旧式转型**（新式转型很容易辨识出来，而分门别类）
- 新式
  - static_cast：适用范围最广的，适用于很多隐式转换，基本数据类型的转换，基类指针与子类指针的相互转换,**或者添加const属性，任何类型转换为void类型**
  - dynamic_cast：主要用来执行“安全向下转型”，决定某对象是否归属继承体系中的某个类型。**static_cast在下行转换时不安全，是因为即使转换失败，它也不返回NULL** ，而dynamic_cast转换失败会返回NULL；对于上行转换，dynamic_cast和static_cast是一样的
  - const_cast：通常用来将对象的**常量性消除**
  - reinterpret_cast：**在比特位级别上进行转换**。它可以把一个指针转换成一个整数，也可以把一个整数转换成一个指针，不能将非32bit的实例转成指针。最普通的用途就是在函数指针类型之间进行转0换，不可移植

<img src="https://raw.githubusercontent.com/Super-DoXCDH/learngit/master/images/image-20200510143914519.png" alt="image-20200510143914519" style="zoom:80%;" />

- 旧式

![image-20200510143938307](https://raw.githubusercontent.com/Super-DoXCDH/learngit/master/images/image-20200510143938307.png)

- 派生类调用基类成员函数（转型写法）

<img src="https://raw.githubusercontent.com/Super-DoXCDH/learngit/master/images/image-20200510155609379.png" alt="image-20200510151450625" style="zoom:80%;" />

- **推荐写法：**

<img src="https://raw.githubusercontent.com/Super-DoXCDH/learngit/master/images/image-20200510151505104.png" alt="image-20200510151505104" style="zoom:80%;" />



## 28.避免返回handles指向对象内部成分

Avoid returning "handles" to object internals.

- 避免返回**handles**（包括references、指针、迭代器）指向对象内部（包括成员变量和不被公开的成员函数），否则会破坏封装性，使const成员函数的行为矛盾，以及发生“空悬虚吊号牌码”



## 29.为“异常安全”而努力

Strive for excption-safe code.

- “异常安全函数”即使发生异常也不会有泄漏资源或允许任何数据结构败坏，区分为以下三种保证： 

  - 基本承诺：异常抛出，程序内的任何事物仍然保持在有效状态下,保证异常抛出不殃及！维持在有效状态下。

  - 强烈保证：异常抛出，程序状态不改变，恢复到调用函数之前的状态（往往能够以copy-and-swap实现出来）

    ![image-20200510155609379](https://raw.githubusercontent.com/Super-DoXCDH/learngit/master/images/image-20200510151450625.png)

  - 不抛掷保证：绝不抛出异常（如内置类型）保证所作的不会有异常！

- 可能的话提供“nothrow保证”，当“强烈保证”不切实际时，就必须提供“基本保证”

- **函数提供的“异常安全保证”通常最高只等于其所调用之各个函数的“异常安全保证”中的最弱者**


## 30：透彻了解inline函数的里里外外

Understand the ins and outs of inlining.

- **将大多数inlining限制在小型、被频繁调用的函数身上**

- Template的具现化与inlining无关（Template放在头文件只是因为一般在编译器完成具现化动作）

- 注：**inline只是给编译器的建议**，大部分的编译器拒绝将太过复杂的函数inlining，隐喻方式是将函数定义于class定义式内构造函数和析构函数往往是inlining的糟糕候选人

  ```c++
  inline void f( ){...};
  void (*pf)( ) = f;
  f();//inlined
  pf();//不被inlined
  ```

- 随着程序库的升级，**inline函数需要重新编译，而non-inline函数只需重新连接**
  

## 31.将文件间的编译依存关系降至最低

Minimize compilation dependencies between files.

- 支持”编译依存最小化”的一般构想是：相依于声明式，不要相依于定义式。基于此构想的两个手段是Handle classes和Interface classes 
- **Handle classes：在.h文件中用class 声明代替include头文件，把成员变量替换为指针的形式，理解的实现方式大致为：**

![image-20200511162146198](https://raw.githubusercontent.com/Super-DoXCDH/learngit/master/images/image-20200511162146198.png)

```c++
// Person.h
#include <string>
using namespace std;

class PersonImp;
class Date;
class Address;

class Person
{   
public:
    Person(const std::string& name,const Date& birthday,const Address& addr);
    string Name() const;
    string Birthday() const;
    string Address() const;

private:
    //string Name;            之前的定义方式,并且以include头文件实现
    //Date Birthday;
    //Address Address;
    std::tr1::shared_ptr<PersonImp> pImpl;     
    //通过提供的PersonImp接口类指针替换实现Person，起到了隔离的作用

// Person.cpp
#include "Person.h"                     //正在实现Person类
#include "PersonImpl.h"                 //使用PersonImp接口类实现Person
                                        //类，必须使用其成员函数，所以要
                                        //include接口类头文件
Person::Person(const std::string& name,const Date& birthday,const Address& addr)
:pImpl(new PersonImpl(name,birthday,addr))
{ }
string Person::Name() const
{
    return pImpl->Name();
}
...                                      //其余函数实现

// PersonImp.h
#include <string>
#include "MyAddress.h"
#include "MyDate.h"
using namespace std;

class PersonImp                 //充当一个接口类，成员函数和Person相同，供
                                //Person类通过指针调用
{
public:
    string Name() const
    {
        return Name;
   }
   ...                          //其余成员函数定义

private:
    string Name;                //放置了所需的外来类对象
    MyAddress Address;
    MyDate Birthday;
};
```

- 总之，此时任何接口类头文件产生的变化只会导致接口类头文件的变化而重新编译，以及Person实现文件由于include了接口类的头文件也要重新编译；**而Person类头文件由于只使用了类的声明式，所以并不会重新编译，因此所有使用Person类的对象的文件也都不需要重新编译了，这样就大大降低了文件之间的编译依存关系**
- 另外，**用Interface Classes也可以降低编译的依赖，实现方法大致是父类只提供虚方法(接口类只有析构和公共成员函数【包括一个factory函数】）**，**而将实现放置在子类中，再通过父类提供的一个特别的静态函数，生成子类对象，通过父类指针来进行操作；**从而子类头文件的改动也不会导致使用该类的文件重新编译，因为用的是父类指针，客户include的是只是父类头文件，该静态方法实现如下：

```c++
//Person.h
class Person{
    public:
    	virtual ~Person();
    	static std::shared_ptr<Person> create(const std::string& name,
               const Date& birthday, const Address& addr);
    	virtual std::string name() const = 0;
    	virtual std::string birthDate() const = 0;
    	virtual std::string address() const = 0;
    	...
    	
}

//realPerson.h
#include<Person.h>
#include<Datefwd.h> //提供前置说明的头文件
#include<Addressfwd.h>

class realPerson:public Person{
    public:
    	realPerson(const std::string& name,const Date& birthday,
				   const Address& addr)
        :theName(name),theBirthDate(birthday),theAddress(addr){}
    	std::string name() const override;//外联
  	    std::string birthDate() const override;
    	std::string address() const override;
    private:
    	std::string theName;
    	Date theBirthday;
    	Address theAddress;
}

//realPerson.cpp
#include<Person.h>
#include<Date.h>
#include<Address.h>
...
std::shared_ptr<Person> 
	Person::create(const std::string& name,const Date& birthday, 
                   const Address& addr)
{
    return std::shared_ptr<Person>(new RealPerson(name, birthday, addr));
    						//智能指针不支持隐式构造！
    						//调用构造函数，返回临时std::shared_ptr<Person>类型对象
}

//使用
std::shared_ptr<Person> pRP(Person::create(name,date,address));//调用copy函数，拷贝至pRP
pRP->name();
...
```

注：

- **对于C++类而言，如果它的头文件变了，那么所有这个类的对象所在的文件都要重编，但如果它的实现文件（cpp文件）变了，而头文件没有变（对外的接口不变），那么所有这个类的对象所在的文件都不会因之而重编**
- **handle类，interface类均是以牺牲额外内存为代价，以‘声明相依’替代‘定义相依’，降低文件间的相依。---加快编译！**
- 编译依存最小化的设计策略： 
  - 1、**如果使用object references或object pointers可以完成任务，就不要用objects** 
  - 2、**如果能够，以class声明式替换class定义式** 
  - 3、**为声明式和定义式提供不同的头文件**



## 32.确定public继承塑膜出is-a关系

Make sure public inheritance models "is-a".

- public继承意味着**is-a**。适用于base class身上的每一件事情也一定适用于derived class身上
- **class Student :publc Person**

![image-20200511201332330](https://raw.githubusercontent.com/Super-DoXCDH/learngit/master/images/image-20200511201332330.png)

## 33.避免遮掩继承来的名称

Avoid hiding inherited names.

- 编译器对于各作用域有查找顺序，所以会造成名称遮掩，各作用域依次为：
  - global作用域
  - namespace
  - base class
  - derived class
  - local作用域
  - 等等
- 可以利用**using声明式**或者**inline转交函数**使遮掩函数重见天日



<img src="https://raw.githubusercontent.com/Super-DoXCDH/learngit/master/images/image-20200511202457552.png" alt="image-20200511202647854" style="zoom:80%;"/>

<img src="https://raw.githubusercontent.com/Super-DoXCDH/learngit/master/images/image-20200511202647854.png" alt="image-20200511202457552" style="zoom:88%;"/>



## 34.区分接口继承和实现继承

Differentiate between inheritance of interface and inheritance of implementation.

- **pure virtual**函数使derived class只继承函数接口,**派生类必须实现**
- **impure virtual**函数使derived class继承函数接口和缺省实现，**一般是让派生类继承接口和缺省实现**
- **non-virtual**函数使derived class继承函数的接口和一份强制性实现，**一般不进行重写**



## 35：考虑virtual函数以外的其他选择

Consider alternatives to virtual functions.

- Non-Virtual Interface手法实现Template Method模式：**令客户通过public non-virtual成员函数间接调用private virtual函数，得以在一个virtual函数被调用之前设定好场景，并在调用结束之后清理场景**

- > ***藉由Function Pointers实现Strategy模式***：**可以由构造函数接受一个指针，指向一个提供的函数，例如：**

```c++
class GameCharacter;                               // 前置声明
int defaultHealthCalc(const GameCharacter& gc);    //缺省函数
class GameCharacter{
public:
    typedef int(*HealthCalcFunc)(const GameCharacter&);
    explicit GameCharacter(HealthCalcFunc hcf=defaultHealthCalc)
        :healthFunc(hcf)
    {}
    int healthValue()const
    { return healthFunc(*this); }
    ……
    private:
        HealthCalcFunc healthFunc;           //函数指针
};
```

- > ***藉由tr1::function完成Strategy模式***：改用一个类型为tr1::function的对象，这样的对象可以保存任何可调用物（callable entity，即函数指针、函数对象、成员函数指针），只要其签名式兼容于需求端，typedef语句修改为：

```c++
typedef std::tr1::function<int (const GameCharacter&)> HealthCalcFunc;

古典的Strategy模式：将继承体系内的virtual函数替换为另一个继承体系内的virtual函数，如下：
class GameCharacter;//forward declaration
class HealthCalcFunc{
public:
    ……
    virtual int calc(const GameCharacter& gc) const
    { …… }
    ……
};

HealthCalcFunc defaultHealthCalc;
class GameCharacter{
public:
    explicit GameCharacter(HealthCalcFunc* phcf=&defaultHealthCalc)
    :pHealthCalc(phcf)
    {}
    int healthValue() const
    { return pHealthClac->calc(*this); }
    ……
private:
    HealthCalcFunc* pHealthCalc;
};
```

> **继承的作用域模型符合实际情况！**
>
> 名称查找规则遵循先local原则。如果函数是virtual函数则要回到derived，如果查到则执行，查不到，则回到base；如果是non-virtual函数则只在本域查找（个人理解）



## 36.绝不重新定义继承而来的non-virtual函数

Never redefine an inherited non-virtual function.

- non-virtual函数是**静态绑定**的，virtual函数是**动态绑定**的，意思是当我们用基类型的指针指向派生类时，重新定义的non-virtual函数并不会表现出多态的性质！

- 另一种观点是：这样的作法还会导致is-a关系矛盾！

  

## 37：绝不重新定义继承而来的缺省参数值

Never redefine a function`s inherited default parameter value.

- 如拒绝这样做，可能会在调用一个定义于derived class内的virtual函数时,使用base class指定的缺省参数值.因为virtual是动态绑定，**但缺省参数是静态绑定（以base型的缺省参数为准）所以我们的做法是在派生类中不再提供缺省参数，避免代码重复！**（基类改变，派生类又要改变一次）
- 使用NVI手法（令public non-virtual函数调用private virtual函数）可以防止缺省参数值被重新定义
- **注：为了运行期效率，c++坚持缺省参数值为静态绑定，防止运行期复杂的决定**



## 38.通过复合塑膜出has-a或“根据某物实现出”

​	Model "has-a" or "is-implemented-in-terms-of" through composition.

- 当复合(composition) **这个术语有许多同义词，包括layering ( 分层)，containment(内含)， aggregation (聚合)和embedding (内嵌)。**发生于**应用域**内的对象之间，表现**has-a**的关系；

  ><img src="https://raw.githubusercontent.com/Super-DoXCDH/learngit/master/images/image-20200512113340202.png" alt="image-20200512113340202" style="zoom:96%;" />

- 当复合它发生于**实现域**内则是表现**is-implemented-in-terms-of**的关系

- 注意list允许重复，但set不允许重复，所以只能用“has-a”

  > ![image-20200512113352299](https://raw.githubusercontent.com/Super-DoXCDH/learngit/master/images/image-20200512113352299.png)
  >
  > <img src="https://raw.githubusercontent.com/Super-DoXCDH/learngit/master/images/image-20200512135314772.png" alt="image-20200512113742506" style="zoom:92%;" />

- 复合的意义和public继承完全不同



## 39.明智而慎重地使用private继承

Use private inheritance judiciously.

- Private继承意味implemented-in-terms-of（只有实现被继承，接口部分应略去）

- 尽可能使用复合，必要时才使用private继承（当derived class想访问base class的protected成分时，或为了重新定义virtual函数时，还有造成EBO（empty base optimization）节省内存时才为必要）

![image-20200512135314772](https://raw.githubusercontent.com/Super-DoXCDH/learngit/master/images/image-20200512142449138.png)

- private继承规则如下：
  - 编译器不会自动将一个derived class对象转换为一个base class对象，不是**is-a**
  - 所有成员都会变成private属性

- 使用复合比使用private继承实现has-a的优点
  - 1，避免派生类对函数的改写
  - 2，降低编译依赖性



## 40.明智而慎重地使用多重继承

Use mutiple inheritance judiciously.

- 多重继承可能从多个base class继承相同名称，也可能导致要命的“菱型(钻石型)多重继承”（base class被多次构造，可以使用virtual继承解决）

![image-20200512142449138](https://raw.githubusercontent.com/Super-DoXCDH/learngit/master/images/image-20200512143325941.png)

- *使用virtual继承导致对象体积大，访问成员变量速度慢等问题*；因此，**非必要不要使用virtual bases，如果要使用，尽可能避免在其中放置数据**（相当于对virtual继承）构建空基优化（EBO)

![image-20200512142603737](https://raw.githubusercontent.com/Super-DoXCDH/learngit/master/images/image-20200512143420322.png)

- 多重继承的一个正当用途是其中一个情节涉及“public继承某个interface class“，和”private继承某个协助实现的class“的两相组合，

<img src="https://raw.githubusercontent.com/Super-DoXCDH/learngit/master/images/image-20200512113742506.png" alt="image-20200512143325941" style="zoom:99%;" />

<img src="https://raw.githubusercontent.com/Super-DoXCDH/learngit/master/images/image-20200512142603737.png" alt="image-20200512143420322" style="zoom:100%;" />

- 单一继承更受欢迎
  

## 41.了解隐式接口和编译器多态

Understand implicit interfaces and compile-time polymorphism.

- ***classe和template都支持接口和多态***
- **对class而言接口是显式的，由函数签名式(*也就是函数名称、参数类型、返回类型*)构成；多态是通过virtual函数发生于运行期**
- **对template而言接口是隐式的(编译器负责找寻最佳匹配)，由有效表达式组成；多态是通过template具现化和函数重载解析发生于编译期**

- 隐式接口就完全不同了。它并不基于函数签名式，而是由有效表达式(valid expressions)组成。

```c++
if( w.size() > 10 && W != someNastyWidget){};//隐式接口:operator>,operator&&,operator!=
```



## 42.了解typename的双重意义

Understand the two meanings of typename.

- 声明template参数时，前缀关键字class和typename可以互换

- **使用typename标识嵌套从属类型名称**（Reason:如果编译器在template中遭遇一个嵌套从属名称，它便假设这名称不是个类型），**但是不得在base class lists或member initialization list内作为base class修饰符**

  ```c++
  template<typename C>//允许使用"typenarme" ( 或"class" )
  void f (const C& container,//不允许使用"typename"
          typename C::iterator iter);//必须使用"typename"
  
  template<typename IterT>
  void workWithIterator(IterT iter)
  {
  	typedef typename std::iterator_traits<IterT>::value_ type value_ type;
  	value_ type temp(* iter) ;
    	...
  }
  
  ```

  

## 43.知道处理模板化基类的名称

​	Know how to access names in templatized base classes.

- template特化版本可能不提供和一般性template相同的接口，所以从Object Oriented C++跨进Template C++时，继承就不像以前那般畅行无阻了
- **为了令c++不进入templatized base classes观察的行为失效**，可以： 
  - 在调用动作之前**加上“this->”**，假设函数将被继承；如果没有，运行会出错
  - 使用**using声明式曝光**（using baseclass::func;）
  - **明白指出**被调用的函数位于base class内（baseclass::func()）

原因:    它知道**base class templates 有可能被特化，而那个特化版本可能不提供和一般性template相同的接口。**因此它往往拒绝在templatized base classes 模板化基类内寻找继承而来的名称。

 **总结：指涉 template base class members需要提前告诉编译器，它的存在！**因为没有具现之前，编译器拒绝进入template base class 观察！



## 44：将参数无关代码抽离template

Factor parameter-independent code out of templates.

> linkers 会合并完全相同的函数实现码，对于不同参数具现的模板，会产生许多版本！
>
> SquareMatrix<double,3>与SquareMatrix<double,4>实现码不同，产生两个版本！

- **非类型模板参数**造成的代码膨胀，**以函数参数或者class成员变量替换template参数**
- **类型模板参数**造成的代码膨胀（比如有着二进制表述相同的int，long），可以让具有完全相同二进制表述的**具现类型共享实现码（instantiation types）**​(:sos:)



## 45：运用成员函数模版接收所有兼容类型

Use member function templates to accept "all compatible types."

- **同一个template的不同具现体**( instantiations)之间并**不存在什么与生俱来的固有关系**

- 请使用成员函数模版生成“可接受所有兼容类型”的函数

![image-20200513141129330](https://raw.githubusercontent.com/Super-DoXCDH/learngit/master/images/image-20200513151106145.png)

```c++
temmplate<typename T>
class SmartPtr{
public:
    template<typename U>
    SmartPtr(const SmartPtr<U>& other)     //泛化copy构造函数
        ： heldPtr(other.get()){...}       //只有当“存在某个隐式转换可将U*                      
                                           //转换为T*”时才能通过编译，从而
                                           //约束转换行为
    T* get() const {return heldPtr;}
    ...
private:
    T* heldPtr;                            //持有的内置指针
};
/**
上面的泛化copy构造函数并未被声明为explicit。那是蓄意的，因为原始指
针类型之间的转换(例如从derived class指针转为base class 指针)是隐式转换，无
需明白写出转型动作(cast) ，所以让智能指针仿效这种行径也属合理。在模板化
构造函数(templatized constructor)中略去explicit就是为了这个目的。
**/
template<class T>
class shared_ptr {
public:
    template<class Y>
      explicit shared_ptr(Y* p);
    temlate<class Y>
      shared_ptr(shared_ptr<Y>const& r);//隐式构造：运行不同shared_ptr类型隐式转换
    temlate<class Y>
      explicit shared_ptr(weak_ptr<Y>const& r);
    temlate<class Y>
      explicit shared_ptr(auto_ptr<Y>& r);
    template<class Y>
      shared_ptr& operator=(shared_ptr<Y>const& r);
    template<class Y>
      shared_ptr& operator=(auto_ptr<Y>& r);
}
```

- T与Y相同，泛化copy构造函数会被具现化为正常的copy构造函数（**允许同类型shared_ptr转换**）

![image-20200513151106145](https://raw.githubusercontent.com/Super-DoXCDH/learngit/master/images/image-20200513155454389.png)

- 即使声明了“泛化拷贝构造函数”和“泛化的赋值操作符”，**仍然需要声明正常的拷贝构造函数和拷贝赋值操作符**（*泛化模板，不能阻止编译器生成默认的构造和赋值函数*）



## 46：需要类型转换时请为模版定义非成员函数

Define non-member functions inside templates when type conbersions are desired.

- 当我们编写一个class template，而它所提供之“与此template相关的”**函数支持“所有参数之隐式类型转换**”时，请将那些函数**定义为“class template内部的friend函数”**，例如：

```
template <typename T>
class Rational{
public:
    …
    friend const Rational<T> operator* (const Rational<T>& lhs, 
                                        const Rational<T>& rhs)
    {                                                           //定义体
        return Rational (lhs.numerator() * rhs.numerator(),
                         lhs.denominator() * rhs.denominator());
    }
    …
}

```

- 在一个class template内，template名称可被用来作为“template”的简略表达
- ***template实参推导过程中从不将隐式类型转换函数纳入考虑***，而class template并不依赖template实参推导，在生成模板类时就可推导出函数而非函数模板



## 47：请使用traits classes表现类型信息

Use traits classes for information about types.

- **Traits classes 使得“类型相关信息”在编译期可用**。它们以 templates 和 “templates 特化”完成实现，如下：

```c++
template<...>                 //自定义迭代器
class deque{
public:
    class iterator{
    public:
        //嵌套的typedef迭代器分类
        typedef random_access_iterator_tag iterator_category;  
    };
};

```

```c++
template<typename IterT>
struct iterator_traits{
    //用iterator_category表现IterT的类型
    typedef typename IterT::iterator_category iterator_category;
    ...
};
```

**注：**
iterator_traits通过特化版本可以提供希望支持的相关类型（如指针类型）
上述iterator_traits::iterator_category在编译期确定，**而if判定却是运行期** 
**确定**，不仅浪费时间，也造成可执行文件膨胀
整合重载技术后。traits classes 有可能在编译期对类型执行 if…else 测试

- input/output_iterator:向前，写入/读取涂改指针一次！
- foward_iterator:向前写入，读取涂改指针多次！
- bidirectional_iterator:双向读取写入涂改指针多次！
- random_access_iterator: 随机双向读取写入涂改指针多次！

> 继承关系：

![image-20200513155454389](https://raw.githubusercontent.com/Super-DoXCDH/learngit/master/images/image-20200513161907885.png)

```c++
template<typename IterT, typename DistT>
void doAdvance(IterT& iter, DistT d, std::random_access_iterator_tag)//非本模板嵌入从属
                                     //这份实现用于random access迭代器
{
    iter += d;
}
...                                  //用于其它迭代器的实现

```

```c++
template<typename IterT, typename DistT>        //用函数模板获控制函数调用
void advance(IterT &iter, DistT d)              //上述函数并传递类型信息
{               
    doAdvance(iter, d, 
              typename std::iterator_traits<TterT>::iterator_category());//嵌入从属类型
}
```

<img src="https://raw.githubusercontent.com/Super-DoXCDH/learngit/master/images/image-20200513162149346.png" alt="image-20200513161406142" style="zoom:110%;" />

> **模板函数重载，替换if-else**

![image-20200513161907885](https://raw.githubusercontent.com/Super-DoXCDH/learngit/master/images/image-20200513141129330.png)

## 48：认识模板元编程

Be aware of template metaprogramming.

- 模板元编程可将工作**由运行期移至编译期**，因而**得以实现早期错误侦测和更高的执行效率，可能导致较小的可执行文件，较短的运行期，较少的内存需求，**可以解决不少问题

- TMP是图灵完全机！

- 循环用递归实现

  - 计算阶乘：

  <img src="https://raw.githubusercontent.com/Super-DoXCDH/learngit/master/images/image-20200513161406142.png" alt="image-20200513162149346" style="zoom:110%;">

## 49：了解new-handler的行为

Understand the bahavior of the new-handle.

- **当operator new无法满足某一内存分配需求时**，它会抛出异常；**抛出异常之前，也会反复调用一个客户指定的错误处理函数（new-handler）**，调用set_new_handler可以指定该函数

- new-handle函数必须做：

  - 让更多内存可被使用
  - 安装另一个new-handle
  - 卸载new-handle
  - 抛出bad_alloc
  - 不返回，exit或abort
  - (:sos:)
  - **NewHandleHodler可以保证set_new_handle"一次性"特性!**

  <img src="https://raw.githubusercontent.com/Super-DoXCDH/learngit/master/images/image-20200513192552219.png" alt="image-20200513174823447" style="zoom:104.6%;" />

  <img src="https://raw.githubusercontent.com/Super-DoXCDH/learngit/master/images/image-20200513174823447.png" alt="image-20200513174416373" style="zoom:98.5%;" />

  ![image-20200513174112266](https://raw.githubusercontent.com/Super-DoXCDH/learngit/master/images/image-20200513182035943.png)

- **Nothrow（在无法分配足够内存时返回NULL即void 0）**是一个颇为局限的工具，它只适用于内存分配，后继的构造函数调用还是可能抛出异常

```c++
Widget* pw2 = new (std::nothrow) Widget(param);
```



## 50：了解new和delete的合理替换时机

Understand when it makes sense to replace new and delete.

- 有许多理由需要写个自定的new和delete，包括检测错误、改善效能，以及收集使用上的统计数据等等



## 51：编写符合常规的new和delete

Adhere to convention when writing new and delete.

- operator new应该内含一个**无限循环**，并在其中尝试分配内存，**如果它无法满足内存需求，就该调用new-handler。它也应该有能力处理0 bytes申请。class专属版本则还应该处理“比正确大小更大的（错误）申请”**
- **operator delete应该在收到null指针时不做任何事。**class专属版本则还应该处理“比正确大小更大的（错误）申请”（如果大小错误，调用标准版本的operator new和delete）



## 52：写了placement new也要写相应的placement delete

Write placement delete if you write placement new.

- new表达式先后调用operator new和default构造函数(**1.operator new分配heap空间2.构造对象3.返回指针**)
- **当你写一个placement operator new,请确定也写出了对应的placement operator delete.* *如果没有这样做,你的程序可能会发生隐微而时断时续的内存泄漏（运行期系统寻找“参数个数和类型都与operator new相同”的某个operator delete，如果一个带额外参数的operator new没有“带相同额外参数”的对应版operator delete，那么当new的内存分配动作需要取消并恢复旧观时就没有任何operator delete会被调用）***

```c++
class Widget {
public:
    static void* operator new(std::size_ t size, std::ostream& logStream)
    throw (std::bad alloc);
```

- 当你声明placement new和placement delete,请**确定继承体系不要无意识地遮掩了它们的正常版本**

<img src="https://raw.githubusercontent.com/Super-DoXCDH/learngit/master/images/image-20200513174416373.png" alt="image-20200513192552219" style="zoom:94.6%;" />

![image-20200513182035943](https://raw.githubusercontent.com/Super-DoXCDH/learngit/master/images/image-20200513174112266.png)
