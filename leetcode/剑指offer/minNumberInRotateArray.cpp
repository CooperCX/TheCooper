#include <vector>

class Solution {
public:
    int minNumberInRotateArray(std::vector<int> rotateArray) {
        if (rotateArray.size() == 0) {
            return 0;
        }
        int low = 0, high = rotateArray.size() - 1;
        while(high - low > 1) {
            int mid = low + (high - low) / 2;
            if (rotateArray[mid] < rotateArray[high]) {
                high = mid;
            } else if (rotateArray[mid] > rotateArray[high]) {
                low = mid;
            } else {
                high--;
            }
        }
        return std::min(rotateArray[low], rotateArray[high]);
    }
};