#include <vector>


// 使用stl标准库函数
class Solution {
public:
    void reOrderArray(std::vector<int> &array) {
        std::stable_partition(array.begin(), array.end(), [](int v){return (v & 1);});
    }
};

// in-place
class Solution {
public:
    void reOrderArray(std::vector<int> &array) {
        int i = 0, n = array.size();
        for(int j = 0; j < n; j++) {
            if (array[j] & 1) {
                int temp = array[j];
                for (int k = j - 1; k >= i; k--) {
                    array[k + 1] = array[k];
                }
                array[i++] = temp;
            }
        }
    }
};