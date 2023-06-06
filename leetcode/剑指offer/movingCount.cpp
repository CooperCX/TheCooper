#include <vector>

class Solution {
public:
    int movingCount(int threshold, int rows, int cols) {
        std::vector<std::vector<bool>> visit(rows, std::vector<bool>(cols, false));
        return movingCountCore(threshold, rows, cols, 0, 0, visit);
    }
private:
    bool canReach(int threshold, int rows, int cols) {
        int sum = 0;
        while (rows) {
            sum += rows % 10;
            rows /= 10;
        }
        while (cols) {
            sum += cols % 10;
            cols /= 10;
        }
        return sum <= threshold;
    }
    int movingCountCore(int threshold, int rows, int cols, int x, int y, std::vector<std::vector<bool>>& visit) {
        if (x < 0 || y < 0 || x >= rows || y >= cols || visit[x][y] || !canReach(threshold, x, y)) {
            return 0;
        }
        visit[x][y] = true;
        return movingCountCore(threshold, rows, cols, x - 1, y, visit) +
            movingCountCore(threshold, rows, cols, x + 1, y, visit) +
            movingCountCore(threshold, rows, cols, x, y - 1, visit) +
            movingCountCore(threshold, rows, cols, x, y + 1, visit) + 1;
    }
};