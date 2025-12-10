#pragma once
#include <cstddef>
template<typename T, size_t S>
class array {
public:
    T& operator[](size_t index) {
        return m_Data[index];
    }

    const T& operator[](size_t index) const {
        return m_Data[index];
    }

    constexpr size_t size() {
        return S;
    }  
private:
    T m_Data[S];
};