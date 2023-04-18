#pragma once
#include <cstddef>
template<typename T, size_t S>
class array {
public:
    T& operator[](size_t index) {
        return m_data[index];
    }

    const T& operator[](size_t index) const {
        return m_data[index];
    }

    constexpr size_t size() {
        return S;
    }  
private:
    T m_Data[S];
};