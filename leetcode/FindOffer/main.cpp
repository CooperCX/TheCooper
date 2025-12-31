#include <iostream>

#include "./methods/printVector.h"
#include "./methods/排序.h"

int main() {
    std::vector<int> values = {19, 30, 5, 61, 7, 16};
    Sort::bucketSort(values, 2);
    printVector<int>(values);
}