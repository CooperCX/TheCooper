# C++ 11

### 1.1 auto: 编译器根据变量的初始值自动推导类型，可以用于变量、函数返回、形参的类型
### 1.2 decltype: 编译器根据表达式的类型推导类型
```
int i = 1;
decltype(i) j = 2;
```
### 1.3 decltype(auto): auto推到出表达式的类型，再确定变量类型。（C++14）
### 2. default、delete: 预置和弃置的函数
### 3. final: 指定某个虚函数不能再派生类中被重写覆盖，或某个类不能被派生
### 4. override: 指定某个虚函数重写覆盖另一个虚函数，如果出现语法错误的话可以检查出来
###  <font color=red>5. 可变参数模版:</font>模版参数至少包含一个参数模版包，一个参数模版包中可以接收0或者多个模版参数
```
// 可变参数模板以两种方式使用省略号
template<typename ...Args>  // 在参数名称的左侧，表示参数包
class Tuple {
    Tuple(const Args&... args) {}  // 在参数名称的右侧，将参数包扩展为单独的名称
};
```
* 如果需避免出现0个模版参数的情况
```
// 参数模版包必须是模版参数列表中最后一个参数
template<typename T, typename ...Args>
class Tuple {
    Tuple(const T& t, const Args&... args) {}
};
```
* 递归展开参数包
```
template<typename T>
void ShowArgsCore(const T& t) {
    std::cout << t << std::endl;
}

template<typename T, typename ...Args>
void ShowArgsCore(const T& t, const Args&... args) {
    std::cout << t << " ";
    ShowArgsCore(args...);
}

template<typename ...Args>
void ShowArgs(Args&&... args) {
    ShowArgsCore(args...);
}
```
* 逗号表达式展开参数包
```
```
### 6. nullptr代替NULL: 在C中NULL表示((void*)0), 在C++中，nullptr表示((void*)0)，NULL表示0.
### <font color=red>7. 智能指针</font>
* 定义：智能指针是一个类，用来管理指向动态分配的指针，负责自动释放动态分配的内存空间。
* 如何实现自动释放：类对象在生命周期结束时自动调用析构函数，释放动态分配的内存空间。
* 常见的智能指针
    * unique_ptr：作用域智能指针，当作用域结束后自动销毁。不可复制，否则会有两个unique_ptr指向同一个内存，造成多次释放。
    ```
    class Entity {};
    std::unique_ptr<Entity> entity(new Entity());
    std::unique_ptr<Entity> entity = std::make_unique<Entity>(); // C++14才有，推荐这种写法，在构造异常时更加安全。
    ```
    * shared_ptr：基于引用计数的智能指针，当指针的引用计数为0时自动释放。可以拷贝和赋值。
    ```
    std::shared_ptr<Entity> shared_entity = std::make_shared<Entity>(); // C++11就有了
    std::shared_ptr<Entity> shared_entity(new Entity()); // 不推荐这种写法。原因：shared_ptr还需要分配一个空间（控制块）存储引用计数int* pcount，将分配好的entity指针传递给shared_ptr构造函数，会做两次分配，先分配new Entity，再分配控制块。
    ```
    ```
    {
        std::shared_ptr<Entity> e0;
        {
            std::shared_ptr<Entity> e1 = std::make_shared<Entity>();
            e0 = e1;
        }  // 里面的作用域结束时，e1结束，但是并不会释放entity，因为e0还活着，entity的引用计数只是从2变成1
    }  // 外面的作用域结束后，e0结束，此时entity的引用计数变为0，entity被释放
    ```
    * weak_ptr：配合shared_ptr使用，可以拷贝，但不会增加引用计数。避免出现智能指针循环引用。

### 8. lambda表达式
```
[capture](params){function}
capture:
[]表示不使用外部变量
[a]表示使用值传递捕获外部变量a
[&a]表示使用引用传递捕获外部变量a
[=]表示使用值传递捕获所有外部变量
[&]表示使用引用传递捕获所有外部变量
```
* 无捕获的lambda表达式可以隐式转换为函数指针，为有捕获的lambda表达式不可以，需使用std::function<return-type(params)>
```
无捕获
void ForEach(const std::vector<int>& values, void(*func)(int)) {
    for (auto value : values) {
        func(value);
    }
}

auto lambda = [](int value) {std::cout << value << std::endl;};
有捕获
void ForEach(const std::vector<int>& values, const std::function<void(int)>& func) {
    for (auto value : values) {
        func(value);
    }
}
int a = 5;
auto lambda = [a](int value) mutable {std::cout << a << std::endl;};
```
* std::find_if中的用法
```
std::vector values = {1, 2, 5, 3, 4};
auto it = std::find_if(values.begin(), values.end(), [](int i){ return i > 3; });
```

### 9. C++11使用using定义别名，代替typedef
* 重定义一个类型，二者功能相同
```
1. typedef unsigned int uint_t;
2. using unint_t = unsigned int;
```
* 重定义一个模版，typedef不可用于模板别名，using可用于模板别名
```
template<typename T>
using map_str_t = std::map<std::string, T>;

map_str_t<int> map_str_int;
```