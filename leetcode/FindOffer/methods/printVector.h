#include <iostream>
#include <vector>

template<typename T>
void printVector(const std::vector<T>& values) {
    std::cout << "[";
    for (auto value : values) {
        std::cout << value << " ";
    }
    std::cout << "]" << std::endl;
}