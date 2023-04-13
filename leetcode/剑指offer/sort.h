#pragma once

#include <vector>

class Sort {
public:

    /*冒泡排序*/
    void bubbleSort(std::vector<int>& numbers) {
        bool flag = false;
        for (int k = 0; k < numbers.size() - 1; k++) 
        {
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
        mergeSortCore(numbers, temp, 0, length);
    }

private:

    /*归并排序*/
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
};