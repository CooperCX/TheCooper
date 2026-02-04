#include <vector>

class minNumberInRotateArraySolution {
   public:
    int minNumberInRotateArray(std::vector<int> rotateArray) {
        if (rotateArray.empty()) return 0;

        int start = 0, end = rotateArray.size() - 1;
        while (start < end) {
            int mid = start + (end - start) / 2;
            if (rotateArray[mid] > rotateArray[end]) {
                start = mid + 1;
            } else if (rotateArray[mid] < rotateArray[end]) {
                end = mid;
            } else {
                end--;
            }
        }

        return rotateArray[start];
    }
};