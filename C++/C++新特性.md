# C++ 11

### 1. auto: 自动推导变量、函数返回、形参的类型
### 2. default、delete: 预置和弃置的函数
### 3. final: 指定某个虚函数不能再派生类中被重写覆盖，或某个类不能被派生
### 4. override: 指定某个虚函数重写覆盖另一个虚函数
### 5. 可变参数模版: 模版参数至少包含一个参数模版包，一个参数模版包中可以接收0或者多个模版参数
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