#include <vector>

class CountIslandSolution {
public:

    int CountIsland(std::vector<std::vector<char>>& grid) {
        int count = 0;
        int n = grid.size();
        if (n == 0) {
            return count;
        }
        int m = grid[0].size();
        if (m == 0) {
            return count;
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] == '1') {
                    CountIslandCore(grid, i, j);
                    count++;
                }
            }
        }
        return count;
    }

private:
    void CountIslandCore(std::vector<std::vector<char>>& grid, int x, int y)
    {
        int n = grid.size();
        int m = grid[0].size();
        if (x < 0 || x >= n || y < 0 || y >= m || grid[x][y] == '0') {
            return;
        }
        grid[x][y] = '0';
        CountIslandCore(grid, x - 1, y);
        CountIslandCore(grid, x + 1, y);
        CountIslandCore(grid, x, y - 1);
        CountIslandCore(grid, x, y + 1);
    }
};