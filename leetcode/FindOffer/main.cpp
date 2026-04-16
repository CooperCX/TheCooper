#include "./methods/912-排序数组.h"
#include "./methods/printVector.h"

int main() {
    std::vector<int> values = {19, 30, 5, 61, 7, 16};
    Sort::bucketSort(values, 2);
    printVector<int>(values);
}