#pragma once
#include <cstddef>
#include <cstring>

class String {
public:
    String() = default; // 预置函数
    String(const char* string) {  // 赋值构造, String string1("hello world");
        m_Size = strlen(string);
        m_Data = new char[m_Size + 1];
        memcpy(m_Data, string, m_Size);
        m_Data[m_Size] = '\0';
    }
    String(const String& other) {  // 拷贝构造, String string2(string1);
        m_Size = other.m_Size;
        m_Data = new char[m_Size];
        memcpy(m_Data, other.m_Data, m_Size);
    }
    String(String&& other) {  // 移动构造, String string3(std::move(string1));
        m_Size = other.m_Size;
        m_Data = other.m_Data;
        other.m_Size = 0;
        other.m_Data = nullptr;
    }
    String& operator=(const String& other) {  // 拷贝赋值, String string4 = string1;
        delete[] m_Data;
        m_Size = other.m_Size;
        m_Data = new char[m_Size];
        memcpy(m_Data, other.m_Data, m_Size);
        return *this;
    }
    String& operator=(String&& other) {  // 移动赋值, String string5 = std::move(string1);
        if (&other != this) {
            delete[] m_Data;
            m_Size = other.m_Size;
            m_Data = other.m_Data;
            other.m_Size = 0;
            other.m_Data = nullptr;
        }
        return *this;
    }
    String& append(const String& other) {
        char* new_Data = new char[m_Size + other.m_Size + 1];
        memcpy(new_Data, m_Data, m_Size);
        memcpy(m_Data + sizeof(char) * m_Size, other.m_Data, other.m_Size);
        m_Data[m_Size] = '\0';
        m_Data = new_Data;
        m_Size += other.m_Size;

        return *this;
    }
    ~String() {
        delete[] m_Data;
    }
private:
    char* m_Data;
    size_t m_Size;
};