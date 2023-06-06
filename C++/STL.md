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
* 迭代器是如何实现的：迭代器内部保存一个和容器相关联的指针，并对各种运算符进行重载。

## 算法
* 算法种类：质变算法，非质变算法
    * 质变算法：会改变元素的内容，拷贝，删除，替换等
    * 非质变算法：不会改变元素的内容，排序，遍历，技术，查找等

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