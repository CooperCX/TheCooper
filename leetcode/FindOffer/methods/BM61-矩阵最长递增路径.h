#include <vector>
#include <algorithm>

class MatirxLongestPathSolution {
public:
    int solve(std::vector<std::vector<int>>& matrix) {
        int n = matrix.size();
        int m = matrix[0].size();
        if (n == 0 || m == 0) {
            return 0;
        }
        int result = 0;
        std::vector<std::vector<int>> dp(n, std::vector<int>(m));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                result = std::max(result, Core(matrix, i, j, dp));
            }
        }
        return result;
    }

private:
    std::vector<std::vector<int>> dirs = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    int Core(std::vector<std::vector<int> >& matrix, int x, int y, std::vector<std::vector<int>>& dp) {
        if (dp[x][y] != 0) {
            return dp[x][y];
        }
        int n = matrix.size();
        int m = matrix[0].size();
        dp[x][y] = 1;
        for (int i = 0; i < 4; i++) {
            int new_x = x + dirs[i][0];
            int new_y = y + dirs[i][1];
            if (new_x >= 0 && new_x < n && new_y >= 0 && new_y < m &&
                matrix[new_x][new_y] > matrix[x][y])
            {
                dp[x][y] = std::max(dp[x][y], Core(matrix, new_x, new_y, dp) + 1);
            }

        }

        return dp[x][y];
    }
};