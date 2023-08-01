#pragma once

#include <vector>
#include <algorithm>
#include <cmath>
class Sort {
public:

    /*冒泡排序：将最大元素放到最后*/
    static void bubbleSort(std::vector<int>& numbers) {
        int n = numbers.size();
        for (int k = 0; k < n - 1; k++) {
            bool flag = false;
            for (int i = 0; i < n - 1 - k; i++) {
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

    /*插入排序：将当前元素插入到应在的位置*/
    static void insertionSort(std::vector<int>& numbers) {
        int n = numbers.size();
        for (int k = 1; k < n; k++) {
            int key = numbers[k];
            int i = k - 1;
            while (i >= 0 && numbers[i] > key) {
                numbers[i + 1] = numbers[i];
                i--;
            }
            numbers[i + 1] = key;
        }
    }

    /*归并排序：将数组对分，排序后再归并*/
    static void mergeSort(std::vector<int>& numbers) {
        int n = numbers.size(); // implicit
        std::vector<int> temp(n, 0);
        mergeSortCore(numbers, temp, 0, n - 1);
    }

private:

    /*归并排序辅助函数*/
    static void mergeSortCore(std::vector<int>& numbers, std::vector<int>& temp, int start, int end) {
        if (start >= end) {
            return;
        }
        int mid = start + (end - start) / 2;
        int lstart = start, lend = mid, rstart = mid + 1, rend = end;
        mergeSortCore(numbers, temp, lstart, lend);
        mergeSortCore(numbers, temp, rstart, rend);

        int index = start;
        while (lstart <= lend && rstart <= rend) {
            temp[index++] = (numbers[lstart] < numbers[rstart]) ? numbers[lstart++] : numbers[rstart++];
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

public:
    /*基数排序：依次对元素个十百位上的数字进行排序*/
    static void radixSort(std::vector<int>& numbers) {
        int n = numbers.size();
        int maxNum = *std::max_element(numbers.begin(), numbers.end());
        std::vector<int> temp(n);
        int radix = 1;
        while (radix <= maxNum) {
            std::vector<int> count(10, 0);
            for (int i = 0; i < n; i++) {
                int k = (numbers[i] / radix) % 10;
                count[k]++;
            }
            for (int i = 1; i < 10; i++) {
                count[i] += count[i - 1];
            }
            for (int i = n - 1; i >= 0; i--) {
                int k = (numbers[i] / radix) % 10;
                temp[--count[k]] = numbers[i];
            }
            for (int i = 0; i < n; i++) {
                numbers[i] = temp[i];
            }
            radix *= 10;
        }
    }

/*-------------------👆稳定排序：相同大小的元素的前后顺序在排序后没有改变👆----------------------*/

    /*选择排序：选择当前元素后面的最小元素，并交换*/
    static void selectionSort(std::vector<int>& numbers) {
        int n = numbers.size();
        for (int i = 0; i < n; i++) {
            int min_index = i;
            for (int j = i + 1; j < n; j++) {
                if (numbers[j] < numbers[min_index]) {
                    min_index = j;
                }
            }
            std::swap(numbers[i], numbers[min_index]);
        }
    }

    /*希尔排序：以gap为单位的插入排序*/
    static void shellSort(std::vector<int>& numbers) {
        int n = numbers.size();
        int gap = n / 2;
        while (gap > 0) {
            for (int i = gap; i < n; i++) {
                int j = i - gap;
                int key = numbers[i];
                while (j >= 0 && numbers[j] > numbers[i]) {
                    numbers[j + gap] = numbers[j];
                    j -= gap;
                }
                numbers[j + gap] = key;
            }
            gap /= 2;
        }
    }

    /*快速排序：递归方法，找到一个元素的位置，将数组划分为两半，依次再排序*/
    static void quickSort(std::vector<int>& numbers, int start, int end) {
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

    /*堆排序*/
    static void heapSort(std::vector<int>& numbers) {
        int n = numbers.size();
        // 初始化
        for (int i = (n - 2) / 2; i >= 0; i--) {
            heapify(numbers, n, i);
        }
        for (int i = 0; i < n - 1; i++) {
            std::swap(numbers[0], numbers[n - 1 - i]);
            heapify(numbers, n - i - 1, 0);
        }
    }

private:
    /*堆排序辅助函数*/
    static void heapify(std::vector<int>& numbers, int n, int i) {
        int left = i * 2 + 1, right = i * 2 + 2;
        int max = i;
        while (left < n && numbers[left] > numbers[max]) {
            max = left;
        }
        while (right < n && numbers[right] > numbers[max]) {
            max = right;
        }
        if (max != i) {
            std::swap(numbers[i], numbers[max]);
            heapify(numbers, n, max);
        }
    }

public:
    /*计数排序：记录每个元素出现的次数*/
    static void countSort(std::vector<int>& numbers) {
        int n = numbers.size();
        int vecSize = *std::max_element(numbers.begin(), numbers.end()) + 1;
        std::vector<int> vec(vecSize, 0);
        for (int i = 0; i < n; i++) {
            vec[numbers[i]]++;
        }
        numbers.clear();
        for (int i = 0; i < vecSize; i++) {
            if ((vec[i]--) > 0) {
                numbers.push_back(i);
            }
        }
    }

    /*桶排序：将数组分成bucketSize个桶，每个桶使用插入排序*/
    static void bucketSort(std::vector<int>& numbers, int bucketCount) {
        int n = numbers.size();
        int minNum = *std::min_element(numbers.begin(), numbers.end());
        int maxNum = *std::max_element(numbers.begin(), numbers.end());
        int bucketSize = std::floor(maxNum - minNum) / bucketCount + 1;
        std::vector<std::vector<int>> buckets(bucketCount);
        for (int i = 0; i < n; i++) {
            buckets[(numbers[i] - minNum) / bucketSize].push_back(numbers[i]);
        }
        numbers.clear();
        for (int i = 0; i < bucketCount; i++) {
            insertionSort(buckets[i]);
            for (int j = 0; j < bucketSize; j++) {
                numbers.push_back(buckets[i][j]);
            }
        }
    }
};