#include <vector>

class findNumberIn2DArrayFindSolution {
public:
    bool findNumberIn2DArrayFind(int target, std::vector<std::vector<int>> array) {
        if (array.size() == 0) {
            return false;
        }
        int col = array.size();
        if (array[0].size() == 0) {
            return false;
        }
        int row = array[0].size();
        auto j = row - 1;
        auto i = 0;
        while(j >= 0 && i < col) {
            if (array[i][j] > target) {
                j--;
            } else if (array[i][j] < target) {
                i++;
            } else {
                return true;
            }
        }
        return false;
    }
};