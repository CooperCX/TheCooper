#include <vector>

class findNumberIn2DArrayFindSolution {
   public:
    // 解法：利用矩阵特性的“抽象二叉搜索树”查找（从右上角出发）
    // 时间复杂度 O(M + N) (M为行，N为列，每次比较必剔除一行或一列)，空间复杂度 O(1)

    // 【极大关键点】一定要加上 const&！防止巨大的二维数组被值传递进行深拷贝！
    bool findNumberIn2DArrayFind(int target, const std::vector<std::vector<int>>& matrix) {
        // 【防御性编程】对于二维数组，不仅查外层是否为空，还要查内层是否为空
        if (matrix.empty() || matrix[0].empty()) return false;
        int rows = matrix.size();
        int cols = matrix[0].size();
        // 选定右上角作为起始探索点 (可以想象成 BST 的根节点)
        int i = 0;         // 行索引，从 0 开始 (最上)
        int j = cols - 1;  // 列索引，从最后一列开始 (最右)
        // 只要游标没有冲出矩阵的左下边界 (i冲过下界，或者 j冲过左界)
        while (i < rows && j >= 0) {
            int value = matrix[i][j];

            if (value < target) {
                // 当前值小了，又因为左边更小没有希望，所以放弃当前整行，向下寻找更大值
                i++;
            } else if (value > target) {
                // 当前值大了，又因为下面更大没有希望，所以放弃当前整列，向左寻找更小值
                j--;
            } else {
                // 完美命中
                return true;
            }
        }

        // 游标冲出场地依然没找到
        return false;
    }
};