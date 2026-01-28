#include <vector>

/*顺时针打印矩阵*/
class printMatrixSolution {
   public:
    std::vector<int> printMatrix(std::vector<std::vector<int>> matrix) {
        std::vector<int> res;
        if (matrix.empty() || matrix[0].empty()) {
            return res;
        }
        int cols = matrix[0].size();
        int rows = matrix.size();

        int top = 0, bot = rows - 1;
        int left = 0, right = cols - 1;
        while (top <= bot && left <= right) {
            for (int i = left; i <= right; i++) {
                res.push_back(matrix[top][i]);
            }
            if (++top > bot) {
                break;
            }
            for (int i = top; i <= bot; i++) {
                res.push_back(matrix[i][right]);
            }
            if (--right < left) {
                break;
            }
            for (int i = right; i >= left; i--) {
                res.push_back(matrix[bot][i]);
            }
            if (--bot < top) {
                break;
            }
            for (int i = bot; i >= top; i--) {
                res.push_back(matrix[i][left]);
            }
            if (++left > right) {
                break;
            }
        }
        return res;
    }
};