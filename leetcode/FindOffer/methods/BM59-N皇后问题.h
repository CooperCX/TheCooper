#include <algorithm>
#include <vector>

class NqueenSolution {
   public:
    int Nqueen(int n) {
        if (n <= 0) return 0;
        int result = 0;

        // 分别用来记录：该列、主对角线(左上到右下)、副对角线(右上到左下) 是否已经被占用
        // 使用 vector<bool> 非常轻量且支持 O(1) 冲突判定
        std::vector<bool> cols(n, false);
        // 对角线的规律：
        // 主对角线 (左上到右下) 上的点，其 row - col 为一个常数。为了防负数数组越界，加上 n 改为 row - col + n
        std::vector<bool> diag1(2 * n, false);
        // 副对角线 (右上到左下) 上的点，其 row + col 为一个常数
        std::vector<bool> diag2(2 * n, false);
        backtrack(n, 0, cols, diag1, diag2, result);

        return result;
    }

   private:
    void backtrack(int n, int row, std::vector<bool>& cols, std::vector<bool>& diag1, std::vector<bool>& diag2,
                   int& result) {
        // 递归终止条件：已经成功放满了 N 行（0 到 n-1）
        if (row == n) {
            result++;
            return;
        }
        // 遍历当前这一行所有的列，尝试放置皇后
        for (int col = 0; col < n; col++) {
            int d1 = row - col + n;  // 主对角线映射下标
            int d2 = row + col;      // 副对角线映射下标
            // 【O(1) 冲突检测】如果不合法，直接跳过
            if (cols[col] || diag1[d1] || diag2[d2]) {
                continue;
            }
            // 1. 做选择：在这放皇后
            cols[col] = true;
            diag1[d1] = true;
            diag2[d2] = true;
            // 2. 递归探寻下一行
            backtrack(n, row + 1, cols, diag1, diag2, result);
            // 3. 撤销选择：回溯现场
            cols[col] = false;
            diag1[d1] = false;
            diag2[d2] = false;
        }
    }
};