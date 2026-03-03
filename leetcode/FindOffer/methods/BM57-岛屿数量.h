#include <vector>

class CountIslandSolution {
   public:
    int solve(std::vector<std::vector<char>>& grid) {
        if (grid.empty() || grid[0].empty()) {
            return 0;
        }
        int count = 0;
        int n = grid.size();
        int m = grid[0].size();
        // 1. 遍历二维网格的每一个格子
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                // 2. 一旦发现一块未被访问的陆地 '1'，就说明找到了一整个新岛屿
                if (grid[i][j] == '1') {
                    ++count;  // 岛屿数量加 1

                    // 3. 接着发起一次 DFS，把这个岛屿所有的陆地全部"炸沉" (变成 '0')
                    // 这样以后再遍历到这片区域时，就不会重复计录了
                    dfs(grid, i, j, n, m);
                }
            }
        }
        return count;
    }

   private:
    // 递归函数：深度优先搜索传染。这里增加传入了 n 和 m，避免每次获取的开销。
    // 传递引用的 grid 以便在原地进行"沉岛"修改
    void dfs(std::vector<std::vector<char>>& grid, int x, int y, int n, int m) {
        // 【卫语句 (Guard Clause) 剪枝】
        // 递归终止的条件：
        // 1. 坐标越界 (x < 0 等等)
        // 2. 当前格子不是陆地 '1' (即可能是水域 '0'，或者是被刚刚炸沉的陆地 '0')
        if (x < 0 || x >= n || y < 0 || y >= m || grid[x][y] != '1') {
            return;
        }
        // 把当前陆地 "沉没"，起到 vis 数组或者哈希集合的效果，防止在此区域死循环
        grid[x][y] = '0';
        // 递归向上下左右四个方向蔓延，继续找同属这个岛屿的块进行沉没
        dfs(grid, x - 1, y, n, m);  // 向上搜
        dfs(grid, x + 1, y, n, m);  // 向下搜
        dfs(grid, x, y - 1, n, m);  // 向左搜
        dfs(grid, x, y + 1, n, m);  // 向右搜
    }
};