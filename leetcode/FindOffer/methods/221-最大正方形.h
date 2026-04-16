#include <algorithm>
#include <vector>

inline int maximalSquare(std::vector<std::vector<char>>& matrix) {
    if (matrix.empty() || matrix[0].empty()) return 0;

    int m = matrix.size(), n = matrix[0].size();
    std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1, 0));
    int maxSquare = 0;

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (matrix[i][j] == '1') {
                dp[i + 1][j + 1] = std::min({dp[i + 1][j], dp[i][j], dp[i][j + 1]}) + 1;
                maxSquare = std::max(maxSquare, dp[i + 1][j + 1]);
            }
        }
    }

    return maxSquare * maxSquare;
}