#include <vector>
#include <unordered_map>
#include <algorithm>

class recursionSolution {
public:

    std::vector<std::vector<int>> permute(std::vector<int>& num) {
        std::sort(num.begin(), num.end());
        std::unordered_map<int, bool> vis;
        std::vector<int> temp;
        std::vector<std::vector<int>> results;

        premuteCore(num, vis, temp, results);

        return results;
    }

private:
    void premuteCore(const std::vector<int>& num,
                     std::unordered_map<int, bool>& vis,
                     std::vector<int>& temp,
                     std::vector<std::vector<int>>& res) {
        if (temp.size() == num.size()) {
            res.push_back(temp);
            return;
        }
        for (int i = 0; i < num.size(); i++) {
            if (vis[i]) {
                continue;
            }
            temp.push_back(num[i]);
            vis[i] = true;
            premuteCore(num, vis, temp, res);
            temp.pop_back();
            vis[i] = false;
        }
    }
};