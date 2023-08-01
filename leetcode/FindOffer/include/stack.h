#pragma once

template<typename T>
class Node {
public:
    T val;
    Node<T>* next = nullptr;

    Node(T val, Node<T>* next) :
        val(val), next(next) {}
};

template<typename T>
class stack {
public:
    using size_t = unsigned int;
public:
    stack() {
        m_Size = 0;
        m_Head = new Node<T>;
    }

    void push(const T& arg) {
        Node<T>* p = new Node<T>(arg);
        p->next = m_Head->next;
        m_Head->next = p;
        m_Size++;
    }

    void pop() {
        if (m_Head->next != nullptr) {
            Node<T>* temp = m_Head->next;
            m_Head->next = temp->next;
            delete temp;
        }
    }

    T top() {
        if (m_Head->next != nullptr) {
            return m_Head->next->val;
        }
    }

    bool empty() {
        return m_Size == 0;
    }
private:
    size_t m_Size;
    Node<T>* m_Head;
};