#include <iostream>

#include "./methods/printVector.h"
#include "./methods/排序.h"

int main() {
    std::vector<int> values = {19, 30, 5, 61, 7, 16};
    Sort::radixSort(values);
    printVector<int>(values);
}