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
};