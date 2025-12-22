#pragma once

#include <algorithm>
#include <cmath>
#include <utility>
#include <vector>
class Sort {
   public:
    /*冒泡排序：每一次循环将最大的放在最后*/
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

    /*插入排序：将当前元素插入到应在的位置，就是让前面没有比当前元素更大的*/
    static void insertionSort(std::vector<int>& numbers) {
        int n = numbers.size();
        if (n <= 1) {
            return;
        }
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
        int n = numbers.size();  // implicit
        std::vector<int> temp(n, 0);
        mergeSortCore(numbers, temp, 0, n - 1);
    }

   private:
    /*归并排序核心逻辑：分治与合并
     * 范围：[start, end] (左闭右闭)
     */
    static void mergeSortCore(std::vector<int>& numbers, std::vector<int>& temp, int start, int end) {
        // 1. 递归终止条件：
        // 当区间长度为0或1时，认为已经有序，直接返回
        if (start >= end) {
            return;
        }

        // 2. 分解 (Divide)：
        // 找到中点，将数组切割成左右两半
        int mid = start + (end - start) / 2;

        // 3. 治 (Conquer)：
        // 递归地对左右两个子区间进行排序
        // 左区间: [start, mid]
        // 右区间: [mid + 1, end]
        mergeSortCore(numbers, temp, start, mid);

        // 4. 合并 (Merge)：
        // 将两个已经有序的子区间，合并到辅助数组 temp 中
        int i = start;    // 左子区间的起始位置
        int j = mid + 1;  // 右子区间的起始位置
        int k = start;    // temp 数组的当前填写入位置

        while (i <= mid && j <= end) {
            // [稳定性关键]
            // 当左右两边元素相等时 (numbers[i] == numbers[j])，
            // 必须优先选择左边的元素 (numbers[i])。
            // 这样才能保证相同元素在排序后的相对前后顺序不变（即稳定性）。
            if (numbers[i] <= numbers[j]) {
                temp[k++] = numbers[i++];
            } else {
                temp[k++] = numbers[j++];
            }
        }

        // 处理左边剩余的元素
        while (i <= mid) {
            temp[k++] = numbers[i++];
        }

        // 处理右边剩余的元素
        while (j <= end) {
            temp[k++] = numbers[j++];
        }

        // 5. 还原：
        // 将合并好的有序数据，从 temp 拷贝回原数组 numbers
        for (int idx = start; idx <= end; idx++) {
            numbers[idx] = temp[idx];
        }
    }

   public:
    /*基数排序：依次对元素个十百位上的数字进行排序*/
    static void radixSort(std::vector<int>& numbers) {
        if (numbers.empty()) {
            return;
        }
        int n = numbers.size();
        std::vector<int> temp(n, 0);
        int minNum = *std::min_element(numbers.begin(), numbers.end());
        // 如果有负数，后面的k会为负数，导致数组越界
        if (minNum < 0) {
            for (int& num : numbers) {
                num -= minNum;
            }
        }
        int maxNum = *std::max_element(numbers.begin(), numbers.end());
        long long radix = 1;  // 当前排序时的位数，初始1是个位；避免int溢出
        while (radix <= maxNum) {
            std::vector<int> count(10, 0);
            for (int i = 0; i < n; i++) {
                int k = (numbers[i] / radix) % 10;  // 取当前位数上的值
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
        if (minNum < 0) {
            for (int& num : numbers) {
                num += minNum;
            }
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