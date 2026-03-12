#include <string>
#include <vector>

using namespace std;

class Solution {
   public:
    // 主函数：遍历每一个点作为潜在的起点
    bool exist(vector<vector<char>>& board, string word) {
        // 防御性判断
        if (board.empty() || board[0].empty() || word.empty()) {
            return false;
        }

        int rows = board.size();
        int cols = board[0].size();

        // 双重循环，把棋盘上每一个点都作为 dfs 的起点试一遍
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                // 如果从点 (r, c) 出发能找到完整的 word，直接全剧终返回 true
                if (dfs(board, word, 0, r, c)) {
                    return true;
                }
            }
        }

        // 所有起点都没戏，那就真的没了
        return false;
    }

   private:
    // 深度优先搜索核心函数
    // 注意：board 和 word 必须加引用 &，否则每次递归都会发生可怕的深拷贝！
    bool dfs(vector<vector<char>>& board, const string& word, int index, int r, int c) {
        // 法宝一：成功的出口。当需要找的字符索引 index 已经达到了单词的长度，说明全找完了！
        if (index == word.length()) {
            return true;
        }

        // 法宝二：失败的出口。越界了、或者当前格子的字母根本不是我们此时想要的
        if (r < 0 || r >= board.size() || c < 0 || c >= board[0].size() || board[r][c] != word[index]) {
            return false;
        }

        // 法宝三：做标记。将当前这个有用的字母先存起来，然后把它原位置改成一个废弃符 '#'
        // 这样只要接下来的四路探索遇到 '#', 因为永远不等于 word 里的英文字母，直接被拦在失败的出口
        char temp = board[r][c];
        board[r][c] = '#';

        // 兵分四路：上下左右探一探。只要有一条路通了（返回 true），我们就沾光算通了。
        bool found = dfs(board, word, index + 1, r - 1, c) ||  // 上
                     dfs(board, word, index + 1, r + 1, c) ||  // 下
                     dfs(board, word, index + 1, r, c - 1) ||  // 左
                     dfs(board, word, index + 1, r, c + 1);    // 右

        // 法宝四：撤销标记（回溯）。我们无论探路成功或失败，从当前格子退回去之前，
        // 都要把格子恢复原状（把藏起来的字母放回去）。
        // 这是因为：就算我们失败了，别人（其他起点出发的路径）可能还要用这个格子！
        board[r][c] = temp;

        return found;
    }
};
