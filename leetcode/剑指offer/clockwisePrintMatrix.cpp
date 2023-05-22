#include <vector>

/*顺时针打印矩阵*/
class Solution {
public:
    std::vector<int> printMatrix(std::vector<std::vector<int>> matrix) {
        int n = matrix[0].size();
        int m = matrix.size();

        std::vector<int> res;
        if (m == 0) {
            return res;
        }
        int top = 0, bot = m - 1;
        int left = 0, right = n - 1;
        while (top <= right && left <= right) {
            for (int j = left; j <= right; j++) {
                res.push_back(matrix[top][j]);
            }
            if (++top > bot) {
                break;
            }
            for (int j = top; j <= bot; j++) {
                res.push_back(matrix[j][right]);
            }
            if (--right < left) {
                break;
            }
            for (int j = right; j >= left; j--) {
                res.push_back(matrix[bot][j]);
            }
            if (--bot < top) {
                break;
            }
            for (int j = bot; j >= top; j--) {
                res.push_back(matrix[j][left]);
            }
            if (++left > right) {
                break;
            }
        }
        return res;
    }
};