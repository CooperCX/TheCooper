#pragma once

template<typename T>
class Shared_Ptr {
public:
    Shared_Ptr(T* ptr) : m_Ptr(ptr), m_pcount(new int(1)) {}

    Shared_Ptr(const Shared_Ptr& other) : m_Ptr(other.m_Ptr), m_pcount(other.m_pcount) {
        *(m_pcount)++;
    }

    Shared_Ptr<T>& operator=(const Shared_Ptr& other) {
        if (this != &other) {
            m_Ptr = other.m_Ptr;
            m_pcount = other.m_pcount;
            *(other.m_pcount)++;
        }
        return *this;
    }

    T operator*() {
        return *m_Ptr;
    }

    T* operator->() {
        return m_Ptr;
    }
    
    ~Shared_Ptr() {
        if (--(*(m_pcount)) == 0) {
            delete m_Ptr;
            m_Ptr = nullptr;
            delete m_pcount;
            m_pcount = nullptr;
        }
    }
private:
    T* m_Ptr;
    int* m_pcount;
};