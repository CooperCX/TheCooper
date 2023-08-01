#include <iostream>
#include "./methods/sort.h"
#include "./methods/printVector.h"

int main() {
    std::vector<int> values = {1, 2, 5, 3, 4, 8, 7, 6};
    Sort::bucketSort(values, 4);
    printVector<int>(values);
}