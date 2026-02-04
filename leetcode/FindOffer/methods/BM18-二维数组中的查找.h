#include <vector>

class findNumberIn2DArrayFindSolution {
   public:
    bool findNumberIn2DArrayFind(int target, std::vector<std::vector<int>> matrix) {
        if (matrix.empty() || matrix[0].empty()) return false;

        int rows = matrix.size();
        int cols = matrix[0].size();

        int i = 0, j = cols - 1;
        while (i < rows && j >= 0) {
            int value = matrix[i][j];
            if (value < target) {
                i++;
            } else if (value > target) {
                j--;
            } else {
                return true;
            }
        }
        return false;
    }
};