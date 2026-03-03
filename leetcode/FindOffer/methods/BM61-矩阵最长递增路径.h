#include <algorithm>
#include <vector>

class MatirxLongestPathSolution {
   public:
    int solve(std::vector<std::vector<int>>& matrix) {
        // 【关键修复】必须先判空，再获取尺寸，防崩大杀器
        if (matrix.empty() || matrix[0].empty()) {
            return 0;
        }
        int n = matrix.size();
        int m = matrix[0].size();
        int max_len = 0;

        // 记忆化矩阵 dp，初始化为 0。dp[i][j] 表示从 (i, j) 出发的最长递增路径长度
        std::vector<std::vector<int>> dp(n, std::vector<int>(m, 0));
        // 尝试把网格里的每一个点都当作起点搜索一遍
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                max_len = std::max(max_len, dfs(matrix, dp, i, j, n, m));
            }
        }
        return max_len;
    }

   private:
    // 将方向数组定义为 constexpr 的原生静态二维数组，0内存分配开销，速度最快
    constexpr static int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    // 【规范推荐】matrix 声明为 const 引用表示不被修改。把 n, m 带进来减少函数内的查询。
    int dfs(const std::vector<std::vector<int>>& matrix, std::vector<std::vector<int>>& dp, int x, int y, int n,
            int m) {
        // 1. 【记忆化搜索的核心】如果这个点之前已经计算过了（不为0），直接返回登记好的结果，极速剪枝！
        if (dp[x][y] != 0) {
            return dp[x][y];
        }
        // 一个格子自己这一个点的路径长度是 1
        int current_max = 1;
        // 2. 尝试向四个方向走
        for (int i = 0; i < 4; i++) {
            int next_x = x + dirs[i][0];
            int next_y = y + dirs[i][1];
            // 判断下一脚踩的坐标有没有越界，且值是否严格大于当前格子（递增要求）
            if (next_x >= 0 && next_x < n && next_y >= 0 && next_y < m && matrix[next_x][next_y] > matrix[x][y]) {
                // 3. 递归寻找下一步的最长路径，加上自己这 1 个格子的长度
                current_max = std::max(current_max, dfs(matrix, dp, next_x, next_y, n, m) + 1);
            }
        }
        // 把好不容易算出来的这个点的最长可能值，存进 dp 里
        dp[x][y] = current_max;

        return current_max;
    }
};