#include <vector>

class Solution {
public:
    bool hasPath(char* matrix, int rows, int cols, char* str)
    {
        if (str == nullptr || rows < 1 || cols < 1) {
            return false;
        }
        std::vector<std::vector<char>> board(rows, std::vector<char>(cols));
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                board[i][j] = matrix[i * cols + j];
            }
        }
        std::vector<std::vector<bool>> visit(rows, std::vector<bool>(cols, false));
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (dfs(board, str, 0, i, j, visit)) {
                    return true;
                }
            }
        }
        return false;
    }
private:
    bool dfs(const std::vector<std::vector<char>> board, char* str, int index, int x, int y, std::vector<std::vector<bool>>& visit) {
        if (index >= strlen(str)) {
            return true;
        }
        if (x < 0 || y < 0 || x >= board.size() || y >= board[0].size() || visit[x][y]) {
            return false;
        }
        if (board[x][y] != str[index]) {
            return false;
        }
        visit[x][y] = true;
        if (dfs(board, str, index + 1, x - 1, y, visit) ||
            dfs(board, str, index + 1, x + 1, y, visit) ||
            dfs(board, str, index + 1, x, y - 1, visit) ||
            dfs(board, str, index + 1, x, y + 1, visit)) {
            return true;
        }
        visit[x][y] = false;
        return false;
    }
};