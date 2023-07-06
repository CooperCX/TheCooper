# STL：标准模版库 standard template library

## 什么是STL
* 三大组件：容器（container），算法（algorithm），迭代器（iterator）
    * 容器container：存放数据的模版类，分为序列式容器和关联式容器。序列式容器有vector，list等，关联式容器有set，map等。（C++11引入无序关联式容器，又称哈希容器，不同之处在于不会进行默认排序）
    * 算法algorithm：用来操作容器中数据的模版函数，大多数包含在头文件`<algorithm>`中。
    * 迭代器iterator：不暴露容器内部结构的情况下对容器中数据的访问方式。
* 特性：数据结构和算法分离，迭代器是两者之间的胶合剂。

## 迭代器
* 迭代器种类：输入迭代器，输出迭代器，前推迭代器，双向迭代器，随机迭代器
    * 输入迭代器：只读迭代器，只能向前移动一次读取一个元素
    * 输出迭代器：只写迭代器，只能向前移动一次写入一个元素
    * 前推迭代器：读写迭代器，只能向前移动一次读取/写入一个元素（组合输入迭代器和输出迭代器）
    * 双向迭代器：读写迭代器，能够前后移动读取/写入元素（组合前推迭代器，还可以向后移动）
    * 随机迭代器：随机访问迭代器，直接访问任意位置的元素（组合双向迭代器，还可以任意移动）
* 迭代器是如何实现的：迭代器是一种smart pointer，内部保存一个和容器相关联的指针，并对各种运算符进行重载。
* 迭代器相应型别
    * value_type: 迭代器所指对象的型别
    * reference_type: typedef const T& reference_type
    * pointer_type: 迭代器所指对象指针的类型
    * difference_type: 两个迭代器之间的距离 typedef ptrdiff_t difference_type
    * iterator_category: 主要用于大规模的迭代器

## Traits编程技法
* 模版特化：模版全特化、模版偏特化
    * 模版全特化：对全部模版参数进行特化
    ```
    template<typename T>
    class stack {
        ...
    };

    template<>
    class stack<bool> {
        ...
    };
    ```
    * 模版偏特化：对某些模版参数进行特化
    ```
    template<typename T, class Allocator>
    class vector {
        ...
    };

    template<class Allocator>
    class vector<bool, Allocator> {
        ...
    };
    ```
* typename关键字：
    * 在模版参数中，使用typename和class没有区别
    ```
    template<class T> class stack{};
    template<typename T> class stack{};
    ```
    * 默认情况下，C++使用作用域操作符`::`访问的名字不是类型，例如：
    ```
        class A {
            static int a;
            void print(int value) {}
        };

        static A::a = 5;
    ```
    * 当我们希望使用模版类型参数的类型成员时，必须使用typename指明，不能使用class
    ```
    template<typename Iter>
    typename Iter::value_type Get(const Iter& iter) {
        return typename Iter::value_type();
    }
    ```
* 迭代器是算法和容器的粘合剂，是算法访问容器元素的工具。在算法中，有时需要使用迭代器所指对象的类型，因此需要traits类型萃取机制
    * 内嵌类型声明
    ```
    template<typename T>
    class MyIter {
        using value_type = typename T::value_type;
        ...
    };
    ```
    * 中间层iterator_traits是一个类模版，将迭代器的value_type(对应容器的value_type)重定义为iterator_traits的value_type
    ```
    // 通用
    template<typename IterType>
    struct iterator_traits {
        using value_type = typename IterType::value_type;
    };
    // 偏特化
    template<typename IterType>
    struct iterator_traits<IterType *> {
        using value_type = typename IterType;
    };
    template<typename IterType>
    struct iterator_traits<const IterType *> {
        using value_type = typename IterType;
    };
    ```
    * 使用iterator_traits简化代码，统一迭代器和原生指针
    ```
    template<typename Iter>
    typename iterator_traits<Iter>::value_type func(Iter it) {
        return *it;
    }
    ```

## 算法
* 算法种类：质变算法，非质变算法
    * 质变算法：会改变元素的内容，拷贝，删除，替换等
    * 非质变算法：不会改变元素的内容，排序，遍历，计数，查找等

## 容器
* string容器: 字符串类，定义在头文件`<string>`
    * 和C风格字符串的对比
    1. `char*`是一个指针，string是一个字符串类，封装了 `char*`，是 `char*`的容器
    2. string中封装了很多成员方法，find, copy, insert, replace
    3. 不用考虑内存的释放和越界
    4. string和C风格字符串的相互转换
    ```
    // string -> c-style
    std::string string = "string";
    const char* cstr = string.c_str();
    // c-style -> string
    const char* cstr = "cstr";
    std::string str(cstr);
    ```
* vector容器: 数组容器，维护一个动态的线性内存空间，具有自动扩容机制。
    * vector迭代器：普通指针，随机访问迭代器
    * vector如何释放多余的内存空间？
    ```
    std::vector<int> values;
    std::vector<int>(values).swap(values);  // 释放多余的内存，相当于values.shrink_to_fit();
    std::vector<int>().swap(values);        // 释放全部的内存
    // swap()的作用是交换对象，将当前对象和传入同类型的对象进行交换，当前对象是一个临时对象，和传入对象交换后，临时对象拥有了传入对象的内存空间，作用域结束后自动释放
    ```
    * 下标访问：不可越界

* deque容器: 双向开口的连续线性空间，可以在头尾两端对元素进行删除和插入操作。
    * 实现原理：deque容器在逻辑上看是一段连续线性空间，但其实是分段的连续空间组合而成的。为了维护整体性，设计了复杂的迭代器机制。
    * 和vector的区别
    1. vector是单向开口的连续线性空间
    2. deque没有容量，是分段的连续空间，需要时随时可以增加一段线性空间在头或者尾部，没有reserve()空间保留操作

* stack容器: 先进后出（FILO）的数据结构。
    * 只有栈顶的元素才可以被访问，没有迭代器和遍历行为。
    * 入栈push(), 出栈pop(), 获取栈顶top()

* queue容器: 先进先出（FIFO）的数据结构。
    * 有两个出口，允许从一端新增元素，从另一端删除元素
    * 只有出口元素才可以被访问，没有迭代器和遍历行为。
    * push(), pop(), front(), back()

* list容器: 链表是一种在物理上非连续非顺序的数据结构，逻辑顺序是根据链表指针实现的。
    * 链表有一系列的结点组成，每个结点包含存储数据的数据域和指向下一结点的指针域。
    * list容器是一个双向链表，动态存储，没有内存的浪费和溢出，插入和删除灵活，但是开销较大
    * list迭代器：双向迭代器

* set/multiset容器: 所有元素都会根据元素的键值自动排序，不允许两个元素具有相同的键值。
    * set和multiset：multiset允许键值重复，底层实现都是红黑树

* pair: 将一对值first和second组合成一个值，可以具有不同的数据结构

* map/multimap容器: 都会根据元素的键值自动排序，不允许两个元素具有相同的键值
    * map和set之间的区别：set的元素即是键值又是实值；map的元素都是pair，同时拥有键值和实值。
    * map和multimap：multimap允许键值重复，底层实现都是红黑树。
    * 为什么使用红黑树来实现map和set：红黑树能在时间复杂度比较低的情况下实现自动排序。
    * 为什么红黑树能同时实现map和set：使用模版参数，底层是红黑树。
    * unordered_map和map的区别
        * unordered_map不会进行自动排序，底层实现是hash_table；map会进行自动排序，底层实现是RBTree
        * unordered_map适用于高效查询的场景；而map适用于有序数据的场景
    * map插入元素方式
    ```
    std::map<int, std::string> cities;
    // 数组方式
    cities[0] = "shanghai";
    // insert()
    cities.insert(std::pair<int, std::string>(1, "beijing"));
    cities.insert(std::make_pair(2, "shenzhen"));
    cities.insert(std::map<int, std::string>::value_type (3, "guangzhou"));
    ```
    * 下标访问：将key作为下标，如果不存在key则会插入map
    * find()：找到了返回迭代器，找不到返回end()迭代器

## 红黑树
* 红黑树是一个二叉排序树：左子树结点 <= 根结点 <= 右子树结点
* 左子树和右子树同样也是二叉排序树
* 要求
    * 所有结点，非红即黑
    * 根结点是黑
    * 红结点的子节点必为黑
    *从根到NULL任何路径上黑结点数量相同
    * 查找时间为O(logn)

## hash table
* 哈希表（散列表）：根据关键字和值（key-value）直接进行访问的数据结构。
* 原理：通过key和哈希函数Hash(key)计算到对应的value，然后把key-value键值对映射到哈希表的某个区块中。
* 哈希函数：将哈希表中key值映射为键值对存储位置的函数，一般满足几个条件：
    * 易于计算且映射位置均匀分布
    * 计算的到的哈希值是一个固定长度的输出值
* 哈希冲突：key1 != key2, Hash(key1) = Hash(key2)
    * 解决方法
        * 开放地址法：在哈希表中寻找新的“空地址”，(H(i) = Hash(key) + F(i)) \% m
            * 线性探测：F(i) = 1, 2, 3, ..., m - 1
            * 二次探测：F(i) = 1^2, 2^2, 3^2, ...
            * 伪随机探测：F(i) = Random()
        * 链地址法：将具有相同哈希地址的键值对存储在同一个线性链表中，即每个哈希地址处为一个链表。插入或查询时，先找到对应的链表，再在链表上进行插入或查询
            * 每个哈希地址处的链表为桶（bucket），存放bucket的哈希表是vector容器。因此，哈希表具备动态扩容能力。
        * 二者的优劣：链地址法使用更多的存储空间，减少了插入和查询的平均时间

## priority_queue
* 大顶堆：结点的值都大于等于其左右结点的值，`std::priority_queue<Type, Container, std::less<Type>>`默认
* 小顶堆：结点的值都小于等于其左右结点的值，`std::priority_queue<Type, Container, std::greater<Type>>`

## STL适配器（配接器adapter）
* STL中有三个基本容器（序列式）：list、vector、deque
* 容器适配器利用基本容器作为底层，用于适配特定功能
* queue：使用deque或list实现
```
template<typename T, class Container = std::deque<T>>
class queue {};
```
* stack：使用deque或list实现
```
template<typename T, class Container = std::deque<T>>
class stack {};
```
* priority_queue：使用vector或deque实现
```
template<typename T, class Container = std::vector<T>, class Comp = std::less<Container::valueType>>
class priority_queue {};
```

## allocator实现原理
* 空间配置器：容器接收一个模版参数`class Alloc = allocator<T>`，在内部实例一个Alloc对象，完成内存分配和释放，对象构造和析构的工作。
标准接口实现：
* allocate -> ::operator new
* deallocate -> ::operator delete
* construct -> placement new调用构造函数
* destroy -> 调用析构函数

* SGI STL的allocator：标准版本的std::allocator，特殊版本的std::alloc
    * 标准配置器 std::allocator
        * 符合STL标准，在defalloc.h中实现，但是不使用，仅提供一种兼容方法，是对new和delete的简单封装
    * 特殊配置器std::alloc
        * SGI STL的默认配置器，在`<memory>`中实现，包含：
            * stl_uninitialezed.h: 一些用于填充和拷贝大块内存的全局函数
            * stl_construct.h: 负责对象的构造和析构，定义全局函数construct()和destroy()
            * stl_alloc.h: 负责内存的分配和释放，内部有两级配置器
                * 第一级：封装malloc()和free()
                * 第二级：实现自由链表和内存池，用于提升大量小额内存分配的性能
        * 在容器内部无需实例一个对象，直接调用alloc的静态函数
            * static T* allocate(): 分配空间
            * static T* allocate(size_t): 批量分配空间
            * static void deallocate(T*): 释放空间
            * static void deallocate(T*, size_t): 批量释放空间
        * 以上静态函数接口根据分配空间大小，调用不同级的空间配置器，最终都是使用malloc()和free()来分配和释放空间
## std::alloc详解
* 对象构造前的空间分配和对象析构后空间释放，由stl_alloc.h负责，依靠malloc()和free()完成
    * SGI把alloc封装为一个符合STL规格的接口
    ```
    template<typename T, class Alloc>
    class simple_alloc {
    public:
        static T* allocate() {
            return (T*)Alloc::allocate(sizeof(T));
        }
        static T* allocate(size_t N) {
            return (N == 0) ? 0 : (T*)Alloc::allocate(sizeof(T) * N);
        }
        static void deallocate(T* p) {
            Alloc::deallocate(p, sizeof(T));
        }
        static void deallocate(T* p, size_t N) {
            if (N != 0) {
                Alloc::deallocate(p, sizeof(T) * N);
            }
        }
    };
    ```
* 考虑过多分配小额内存可能导致的内存碎片，SGI设计了双层配置器
    * 第一级配置器：直接使用malloc()和free()
        * allocate()直接调用malloc(), deallocate()直接调用free()，realloc()调用realloc()
        * 内存不足：模拟C++的set_new_handler()，处理out-of-memory
            * 的set_new_handler机制：在系统无法满足内存配置要求，抛出异常std::bad_alloc之前，调用一个指定用来解决内存不足的处理例程new_handler
        * allocate()、realloc()在调用malloc()和realloc()不成功时，会调用oom_malloc()和oom_realloc()，后两者内循环调用new_handler。如果用户没有指定new_handler，将抛出异常std::bad_alloc中止程序

    * 第二级配置器：采用内存池memory pool技术（为了减少直接调用系统分配内存，提升性能）
        * 是否开启第二级配置器，取决于_USE_MALLOC宏是否被定义
        * 内存池memory pool通过malloc()得到，如果内存不够，转移到第一级配置器
        * 如果配置内存 > 128 bytes，转移到第一级配置器
        * 根据情况采取不同的配置策略：
            * 当配置内存 > 128 bytes，直接调用第一级配置器
            * 当配置内存 < 128 bytes，调用第二级配置器
        * memory pool负责小额内存的分配和释放。维护16个自由链表free list，各自管理8，16，24，...，128bytes大小的内存（8的倍数）
            * allocate()
            ```
            static void* allocate(size_t n) {
                if (n > 128 bytes) {
                    // 调用第一级配置器
                    return malloc_alloc::allocate(n);
                }
                根据分配的内存大小n，找到对应的free_list
                if (free_list有可用内存) {
                    直接从free_list的头部取出对应的内存;
                } else {
                    调用函数refill()为free list重新填充空间;
                }
            }
            ```
            ```
            // 重新填充空间，新的空间来自内存池，默认取得20个新内存块（内存池空间不足时，可能小于20）
            refill(size_t n) {
                调用chunk_alloc(n, nobjs)，尝试取得nobjs个内存块作为free list的新节点
            }
            ```
            ```
            //
            chunk_alloc(size_t size, int& nobjs) {
                if (内存池能够满足20个内存块的需求) {
                    则直接取出对应大小的空间
                } else if (内存池不能够满足20个内存块的需求，但是能满足一个及以上内存块的需求) {
                    则取出能够满足条件的内存块个数的空间（能取多少就取多少）
                } else (内存池不能满足一个内存块的需求) {
                    1. 内存池中是否有残余内存空间，回收到free list
                    2. 向heap申请空间，补充内存池
                    if (heap空间满足) {
                        分配成功
                    }
                    else (heap空间不足) {
                        malloc失败
                        if(存在足够未用内存块的free list){
                            释放free list编入内存池
                            递归调用chunk_alloc()从内存池中取空间补充free list
                        } else {
                            调用第一级配置器，使用out-of-memory内存处理机制
                            if (处理例程ok) {
                                ok
                            } else {
                                bad_alloc
                            }
                        }
                    }
                }
            }
            ```
            举个例子，假设程序一开始，客端就调用chunk_alloc(32,20),于是 malloc()配置40个32bytes内存块，其中第1个交出，另19个交给free_list[3]维护，余20个留给内存池。接下来客端调用chunk_alloc(64,20)，此时free_list[7]也空空如也，必须向内存池要求支持。内存池只够供应(32*20)/64=10个bytes内存块，就把这10个内存块返回，第一个交给客端，余9个由free_list[7]维护。此时内存池全空。接下来再调用chunk_alloc(96,20)，此时free_list[11]也空空如也，必须向内存池要求支持，而内存池此时也是空的，于是以malloc()配置40+n（附加量）个96bytes内存块，其中交出1个，令19个交个free_list[11]维护，余20+n（附加量）个内存块留给内存池。

            万一山穷水尽，整个system heap空间都不够了（以至于无法为内存池注入源头活水），malloc()行动失败，chunk_alloc()就四处寻找有无“尚有未用区域，且内存块够大”之free lists。找到了就挖一块交出，找不到就调用第一级配置器，第一级配置器其实就是使用malloc()来配置内存，但它有out-of-memory处理机制，或许有机会释放其他的内存拿来此处使用，如果可以，就成功，否则发出bad_alloc异常。
            * deallocate()
            ```
            static void deallocate(void *p, size_t n) {
                if (释放的内存 > 128bytes) {
                    调用第一节配置器
                } else {
                    找到对应的free list，将内存块回收，防护free list的头部
                }
            }
            ```

## 仿函数 Functor
* 仿函数又称为函数对象（Function Object），是一个能行使函数功能的类
* 实现：类内重载了operator()操作符
```
class CompareWithThreshold {
public:
    CompareWithThreshold(const int& t) : threshold(t) {

    }
    bool operator()(int i) {
        return i > threshold;
    }
private:
    int threshold;
};

int main() {
    std::cout << CompareWithThreshold(10)(1) << "\n";
}
```