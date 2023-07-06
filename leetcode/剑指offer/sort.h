#pragma once

#include <vector>
#include <algorithm>
#include <cmath>
class Sort {
public:

    /*冒泡排序*/
    void bubbleSort(std::vector<int>& numbers) {
        bool flag = false;
        for (int k = 0; k < numbers.size() - 1; k++) {
            flag = false;
            for (int i = 0; i < numbers.size() - k - 1; i++) {
                if (numbers[i] > numbers[i + 1]) {
                    std::swap(numbers[i], numbers[i + 1]);
                    flag = true;
                }
            }
            if (!flag) {
                break;
            }
        }
    }

    /*插入排序*/
    void insertionSort(std::vector<int>& numbers) {
        for (int k = 1; k < numbers.size(); k++) {
            int key = numbers[k];
            int i = k - 1;
            while (i >= 0 && key < numbers[i])
            {
                numbers[i + 1] = numbers[i];
                i--;
            }
            numbers[i + 1] = key;
        }
    }

    /*归并排序*/
    void mergeSort(std::vector<int>& numbers) {
        int length = numbers.size(); // implicit
        std::vector<int> temp(length, 0);
        mergeSortCore(numbers, temp, 0, length - 1);
    }

    /*基数排序*/
    void radixSort(std::vector<int>& numbers) {
        int max_number = *(std::max_element(numbers.begin(), numbers.end()));
        std::vector<int> temp(numbers.size());
        std::vector<int> count(10);
        int radix = 1;
        while (radix <= max_number) {
            for (int i = 0; i < 10; i++) {
                count[i] = 0;
            }
            for (size_t i = 0; i < numbers.size(); i++) {
                int k = (numbers[i] / radix) % 10;
                count[k]++;
            }
            for (int i = 1; i < 10; i++) {                    // count要累加
                count[i] = count[i] + count[i - 1];
            }
            for (int i = numbers.size() - 1; i >= 0; i--) {   // 必须是倒序
                int k = (numbers[i] / radix) % 10;
                temp[--count[k]] = numbers[i];
            }
            for (size_t i = 0; i < numbers.size(); i++) {
                numbers[i] = temp[i];
            }
            radix *= 10;
        }
    }

/*-------------------👆稳定排序：相同大小的元素的前后顺序在排序后没有改变👆----------------------*/

    /*选择排序*/
    void selectionSort(std::vector<int>& numbers) {
        int min_index = 0;
        for (int k = 0; k < numbers.size(); k++) {
            min_index = k;
            for (int i = k + 1; i < numbers.size(); i++) {
                if (numbers[i] < numbers[min_index]) {
                    min_index = i;
                }
            }
            std::swap(numbers[k], numbers[min_index]);
        }
    }

    /*希尔排序*/
    void shellSort(std::vector<int>& numbers) {
        int gap = numbers.size() / 2;  //implicit
        while (gap >= 1) {
            for (int i = gap; i < static_cast<int>(numbers.size()); i++) {
                int j  = i - gap;
                int key = numbers[i];
                while (j >= 0 && numbers[j] > key) {
                    numbers[j + gap] = numbers[j];
                    j -= gap;
                }
                numbers[j + gap] = key;
            }
            gap /= 2;
        }
    }

    /*快速排序*/
    void quickSort(std::vector<int>& numbers, int start, int end) {
        if (start >= end) {
            return;
        }
        int pivot = numbers[start];
        int first = start, last = end;
        while (first < last) {
            while (first < last && numbers[last] > pivot) {
                last--;
            }
            if (first < last) {
                numbers[first++] = numbers[last];
            }
            while (first < last && numbers[first] < pivot) {
                first++;
            }
            if (first < last) {
                numbers[last--] = numbers[first];
            }
        }
        numbers[first] = pivot;
        quickSort(numbers, start, first - 1);
        quickSort(numbers, first + 1, end);
    }

    /*归并排序*/
    void mergeSort(std::vector<int>& numbers) {
        int length = numbers.size(); // implicit
        std::vector<int> temp(length, 0);
        mergeSortCore(numbers, temp, 0, length - 1);
    }

    /*堆排序*/
    void heapSort(std::vector<int>& numbers) {
        int n = numbers.size();
        // 初始化
        for (int i = (n - 2) / 2; i >= 0; i--) {
            heapify(numbers, n, i);
        }

        for (int i = 0; i < n; i++) {
            std::swap(numbers[0], numbers[n - i - 1]);
            heapify(numbers, n - i - 1, 0);
        }
    }

    /*计数排序*/
    void countSort(std::vector<int>& numbers) {
        int vecCountLength = (*std::max_element(numbers.begin(), numbers.end())) + 1;
        std::vector<int> vecCount(vecCountLength, 0);
        for (size_t i = 0; i < numbers.size(); i++) {
            vecCount[numbers[i]]++;
        }
        numbers.clear();
        for (int i = 0; i < vecCountLength; i++) {
            int Count = vecCount[i];
            while (Count > 0) {
                numbers.push_back(i);
                Count--;
            }
        }
    }

    /*桶排序*/
    void bucketSort(std::vector<int>& numbers, int bucketSize) {
        int min = *(std::min_element(numbers.begin(), numbers.end()));
        int max = *(std::max_element(numbers.begin(), numbers.end()));

        int bucketCount = std::floor(max - min) / bucketSize + 1;
        std::vector<std::vector<int>> buckets(bucketSize);
        for (size_t i = 0; i < numbers.size(); i++) {
            buckets[std::floor(numbers[i] - min) / bucketCount].push_back(numbers[i]);
        }

        numbers.clear();
        for (int i = 0; i < bucketSize; i++) {
            insertionSort(buckets[i]);
            for (size_t j = 0; j < buckets[i].size(); j++) {
                numbers.push_back(buckets[i][j]);
            }
        }
    }

private:

    /*归并排序辅助函数*/
    void mergeSortCore(std::vector<int>& numbers, std::vector<int>& temp, int start, int end) {
        if (start >= end) {
            return;
        }
        int mid = start + (end - start) / 2;
        int lstart = start, lend = mid, rstart = mid + 1, rend = end;
        mergeSortCore(numbers, temp, lstart, lend);
        mergeSortCore(numbers, temp, rstart, rend);

        int index = start;
        while (lstart <= lend && rstart <= rend) {
            temp[index++] = numbers[lstart] < numbers[rstart] ? numbers[lstart++] : numbers[rstart++];
        }
        while (lstart <= lend) {
            temp[index++] = numbers[lstart++];
        }
        while (rstart <= rend) {
            temp[index++] = numbers[rstart++];
        }

        for (int i = start; i <= end; i++) {
            numbers[i] = temp[i];
        }
    }

    /*堆排序辅助函数*/
    void heapify(std::vector<int>& numbers, int n, int i) {
        int l = i * 2 + 1, r = i * 2 + 2;
        int max = i;
        if (l < n && numbers[l] > numbers[max]) {
            max = l;
        }
        if (r < n && numbers[r] > numbers[max]) {
            max = r;
        }
        if (max != i) {
            std::swap(numbers[max], numbers[i]);
            heapify(numbers, n, max);
        }
    }
};