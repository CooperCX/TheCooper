#include <cstddef>
#include <utility>

// [知识点：迭代器本质是对底层指针的封装与特化]
template <typename VectorType>
class VectorIterator {
public:
    // [知识点：Traits 类型萃取，使得标准库算法如 std::sort 也能识别和通用此迭代器]
    using value_type = typename VectorType::value_type;
    using pointer_type = value_type*;
    using reference_type = value_type&;

public:
    VectorIterator(pointer_type ptr) : ptr_(ptr) {}

    pointer_type operator->() { return ptr_; }

    reference_type operator*() { return *ptr_; }

    // 前置++: 修改自身并返回
    VectorIterator& operator++() {
        ptr_++;
        return *this;
    }

    // 后置++: 缓存老状态，自增自身，返回老状态
    VectorIterator operator++(int) {
        VectorIterator temp = *this;
        ptr_++;
        return temp;
    }

    bool operator==(const VectorIterator& other) const { return ptr_ == other.ptr_; }

    bool operator!=(const VectorIterator& other) const { return !(*this == other); }

private:
    pointer_type ptr_;
};

// [知识点：模板类的数据结构与算法分离原则]
template <typename T>
class Vector {
public:
    // 兼容 STL 标准接口规范的名称映射
    using value_type = T;
    using iterator = VectorIterator<Vector<T>>;

public:
    Vector() { Realloc(2); }

    // [知识点：三法则 (Rule of Three) - 析构函数必须负责清理动态主分内存]
    ~Vector() {
        Clear();
        // [知识点：两段式释放肉体，禁止用 delete[] 处理 raw memory]
        // [知识点：C++14 Sized Deallocation 带大小释放，极速无缝对齐]
        ::operator delete(data_, sizeof(T) * capacity_);
    }

    // [知识点：三法则 - 拷贝构造。禁止浅拷贝防范 Double Free]
    Vector(const Vector& other) {
        size_ = other.size_;
        capacity_ = other.capacity_;

        // [知识点：::operator new 申请未初始化的纯净物理内存 (取代危险的 new T[])]
        data_ = static_cast<T*>(::operator new(sizeof(T) * capacity_));

        for (size_t i = 0; i < size_; ++i) {
            // [知识点：Placement New,在未初始化空间上显式调用拷贝构造复刻魂魄]
            new (&data_[i]) T(other.data_[i]);
        }
    }

    // [知识点：五法则 - 移动构造 (Move Constructor)。直接掠夺内存指针，实现 O(1) 转移]
    // [知识点：noexcept 必加！提供极强异常安全保障，保障 Copy-And-Swap 的正确拦截]
    Vector(Vector&& other) noexcept : data_(other.data_), size_(other.size_), capacity_(other.capacity_) {
        // [知识点：移动后必须切断旧羁绊，严防内存泄露与析构时的 Double Free 灾难]
        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }

    // [知识点：大厂防御性编程 Copy-and-Swap 惯用法。传值产生临时替身，利用局部对象自动释放垃圾机制极其优雅]
    Vector& operator=(Vector other) noexcept {
        Swap(other);

        return *this;
    }

    // [知识点：左值引用入参，触发普通深拷贝逻辑]
    void push_back(const T& data) {
        if (size_ >= capacity_) {
            Realloc(capacity_ == 0 ? 2 : capacity_ + capacity_ / 2);
        }

        // [知识点：原始未初始化内存强行入住]
        new (&data_[size_++]) T(data);
    }

    // [知识点：右值引用入参，深层叠加 std::move 触发底层自带类型内部的极速搬运]
    void push_back(T&& data) {
        if (size_ >= capacity_) {
            Realloc(capacity_ == 0 ? 2 : capacity_ + capacity_ / 2);
        }

        new (&data_[size_++]) T(std::move(data));
    }

    // [知识点：可变参数模板 (Variadic Templates) 与 完美转发 (Perfect Forwarding)]
    // [知识点：性能优化极致 emplace_back，彻底跳过不必要临时对象，直接在数组最深渊实现“原址召唤”]
    template <typename... Args>
    void emplace_back(Args&&... args) {
        if (size_ >= capacity_) {
            Realloc(capacity_ == 0 ? 2 : capacity_ + capacity_ / 2);
        }

        new (&data_[size_++]) T(std::forward<Args>(args)...);
    }

    void pop_back() {
        if (size_ > 0) {
            // [知识点：主动显式调用底层的西析函数清理资源(如解绑底层文件)。只毁灭灵魂，保留肉体堆内存供下次利用]
            data_[--size_].~T();
        }
    }

    // 清空内部所有的驻留残骸
    void Clear() {
        for (size_t i = 0; i < size_; ++i) {
            data_[i].~T();
        }

        size_ = 0;
    }

    void Swap(Vector& other) noexcept {
        std::swap(data_, other.data_);
        std::swap(size_, other.size_);
        std::swap(capacity_, other.capacity_);
    }

    T& operator[](size_t index) { return data_[index]; }
    const T& operator[](size_t index) const { return data_[index]; }

    constexpr size_t size() const { return size_; }

    constexpr size_t capacity() const { return capacity_; }

    iterator begin() { return iterator(data_); }

    iterator end() { return iterator(data_ + size_); }

private:
    // [知识点：STL 核心容器扩容机制 (Reallocation) 与强异常安全保证]
    void Realloc(size_t new_capacity) {
        T* new_data = static_cast<T*>(::operator new(sizeof(T) * new_capacity));

        size_t move_size = size_ < new_capacity ? size_ : new_capacity;

        for (size_t i = 0; i < move_size; ++i) {
            // [知识点：如果不用 move，扩容会导致恐怖的深层次群发冗余拷贝！]
            new (&new_data[i]) T(std::move(data_[i]));
        }

        // [知识点：即使肉体搬新家了，旧壳子仍属“有效未定义状态资源”，务必调用析构火化清理]
        for (size_t i = 0; i < size_; ++i) {
            data_[i].~T();
        }

        ::operator delete(data_, sizeof(T) * capacity_);

        data_ = new_data;
        capacity_ = new_capacity;
        size_ = move_size;
    }

private:
    T* data_ = nullptr;
    size_t size_ = 0;
    size_t capacity_ = 0;
};