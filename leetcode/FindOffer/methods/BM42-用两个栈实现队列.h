#include <stack>

#include "../include/stack.h"
class MyQueue {
   public:
    MyQueue() {}

    void push(int x) { stack1.push(x); }

    int pop() {
        int node = peek();
        stack2.pop();
        return node;
    }

    int peek() {
        if (empty()) return -1;

        if (stack2.empty()) {
            while (!stack1.empty()) {
                stack2.push(stack1.top());
                stack1.pop();
            }
        }
        return stack2.top();
    }

    bool empty() { return stack1.empty() && stack2.empty(); }

   private:
    std::stack<int> stack1;
    std::stack<int> stack2;
};