#pragma once
#include <cstddef>

template<typename VectorType>
class VectorIterator {
public:
    using ValueType = typename VectorType::ValueType;
    using PointerType = ValueType*;
    using ReferenceType = ValueType&;
public:
    VectorIterator(PointerType ptr) : m_Ptr(ptr) {
    }
    bool operator==(const VectorIterator& other) {
        return this->m_Ptr == other.m_Ptr;
    }
    bool operator!=(const VectorIterator& other) {
        return !(*this == other);
    }
    VectorIterator& operator++() {
        m_Ptr++;
        return *this;
    }
    VectorIterator operator++(int) {
        VectorIterator iterator = *this;
        ++(*this);
        return iterator;
    }
    ReferenceType operator[](size_t index) {
        return *(m_Ptr + index);
    }
    ReferenceType operator*() {
        return *m_Ptr;
    }
    PointerType operator->() {
        return m_Ptr;
    }

private:
    PointerType m_Ptr;
};


template<typename T>
class Vector {
public:
    using ValueType = T;
public:
    Vector() {
        ReAlloc(2);
    }
    Vector(const Vector& other) {
        m_Size = other.m_Size;
        m_Capacity = other.m_Capacity;
        // m_Data = new T(m_Capacity);
        m_Data = (T*)::operator new (sizeof(T) * m_Capacity);
        for (size_t i = 0; i < m_Size; i++) {
            // m_Data[i] = other.m_Data[i];
            new (&m_Data[i]) T(other.m_Data[i]);
        }
    }
    Vector(Vector&& other) {
        m_Size = other.m_Size;
        m_Capacity = other.m_Capacity;
        // m_Data = new T(m_Capacity);
        m_Data = (T*)::operator new (sizeof(T) * m_Capacity);
        for (size_t i = 0; i < m_Size; i++) {
            // m_Data[i] = std::move(other.m_Data[i]);
            new (&m_Data[i]) T(std::move(other.m_Data[i]));
        }
        // other.clear();
        // delete[] other.m_Data;
        for (size_t i = 0; i < other.m_Size; i++) {
            other.m_Data[i].~T();
        }
        ::operator delete(other.m_Data, sizeof(T) * m_Capacity);
        other.m_Capacity = 0;
        other.m_Size = 0;
    }
    Vector& operator=(const Vector& other) {
        if (&other == this) {
            return *this;
        }
        m_Size = other.m_Size;
        m_Capacity = other.m_Capacity;
        // m_Data = new T(m_Capacity);
        m_Data = (T*)::operator new (sizeof(T) * m_Capacity);
        for (size_t i = 0; i < m_Size; i++) {
            // m_Data[i] = other.m_Data[i];
            new (&m_Data[i]) T(other.m_Data[i]);
        }
        return *this;
    }
    Vector& operator=(Vector&& other) {
        if (&other == this) {
            return *this;
        }
        m_Size = other.m_Size;
        m_Capacity = other.m_Capacity;
        // m_Data = new T(m_Capacity);
        m_Data = (T*)::operator new (sizeof(T) * m_Capacity);
        for (size_t i = 0; i < m_Size; i++) {
            // m_Data[i] = std::move(other.m_Data[i]);
            new (&m_Data[i]) T(std::move(other.m_Data[i]));
        }
        // other.clear();
        // delete[] other.m_Data;
        for (size_t i = 0; i < other.m_Size; i++) {
            other.m_Data[i].~T();
        }
        ::operator delete(other.m_Data, sizeof(T) * m_Capacity);
        other.m_Capacity = 0;
        other.m_Size = 0;
        return *this;
    }
    ~Vector() {
        delete[] m_Data;
    }
public:
    void push_back(const T& data) {
        if (m_Size >= m_Capacity) {
            ReAlloc(m_Capacity + m_Capacity / 2);
        }
        m_Data[m_Size++] = data;
    }

    void push_back(T&& data) {
        if (m_Size >= m_Capacity) {
            ReAlloc(m_Capacity + m_Capacity / 2);
        }
        m_Data[m_Size++] = std::move(data);
    }

    template<typename... Args>  // 可变参数模版
    void emplace_back(Args&&... args) {
        if (m_Size >= m_Capacity) {
            ReAlloc(m_Capacity + m_Capacity / 2);
        }
        new (&m_Data[m_Size]) T(std::forward<Args>(args)...);  //placement new
        m_Size++;
    }

    T& operator[](size_t index) {
        return m_Data[index];
    }

    const T& operator[](size_t index) const {
        return m_Data[index];
    }

    void pop() {
        if (m_Size == 0) {
            return;
        }
        m_Data[--m_Size].~T();
    }
    void clear() {
        for (size_t i = 0; i < m_Size; i++) {
            m_Data[i].~T();
        }
        m_Size = 0;
    }

    VectorIterator<Vector<T>> begin() {
        return VectorIterator<Vector<T>>(m_Data);
    }

    VectorIterator<Vector<T>> end() {
        return VectorIterator<Vector<T>>(m_Data + m_Size);
    }
    constexpr size_t size() {
        return m_Size;
    }

    constexpr size_t capacity() {
        return m_Capacity;
    }
private:
    void ReAlloc(size_t newCapacity) {
        // shrink
        if (m_Size >= newCapacity) {
            m_Size = newCapacity;
        }
        // increment
        // T* new_Data = new T[newCapacity];
        // 将new操作的开辟空间和构造操作分开执行
        T* new_Data = (T*)::operator new (sizeof(T) * newCapacity); // ::operator new 申请一个指定大小的空间，指针类型为void*，要强制转换才能使用
        for (size_t i = 0; i < m_Size; i++) {
            new_Data[i] = m_Data[i];
        }
        // delete[] m_Data;
        // 将delete操作的析造操作和释放分开执行
        for (size_t i = 0; i < m_Size; i++) {
            m_Data[i].~T();
        }
        ::operator delete(m_Data, sizeof(T) * m_Capacity);

        m_Data = new_Data;
        m_Capacity = newCapacity;
    }

    T* m_Data = nullptr;
    size_t m_Size = 0;
    size_t m_Capacity = 0;
};