#include <vector>
#include <algorithm>

class NqueenSolution {
public:

    int Nqueen(int n) {
        std::vector<int> pos(n);
        int result = 0;
        NqueenCore(n, 0, pos, result);
        return result;
    }

private:
    bool isValid(const std::vector<int>& pos, int row, int col) {
        for (int i = 0; i < row; i++) {
            if (pos[i] == col || std::abs(row - i) == std::abs(col - pos[i])) {
                return false;
            }
        }
        return true;
    }

    void NqueenCore(int n, int row, std::vector<int>& pos, int& res) {
        if (n == row) {
            res++;
            return;
        }
        for (int i = 0; i < n; i++) {
            if (isValid(pos, row, i)) {
                pos[row] = i;
                NqueenCore(n, row + 1, pos, res);
            }
        }
    }
};