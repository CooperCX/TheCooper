#include <vector>
#include <unordered_map>
#include <algorithm>

class recursionUniqueSolution {
public:

    std::vector<std::vector<int>> permute(std::vector<int>& num) {
        std::sort(num.begin(), num.end());
        std::unordered_map<int, bool> vis;
        std::vector<int> temp;
        std::vector<std::vector<int>> results;

        permuteCore(num, vis, temp, results);
        return results;
    }

private:
    void permuteCore(const std::vector<int>& num,
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
            if (i > 0 && num[i] == num[i - 1] && !vis[i - 1]) {
                continue;
            }
            temp.push_back(num[i]);
            vis[i] = true;
            permuteCore(num, vis, temp, res);
            temp.pop_back();
            vis[i] = false;
        }
    }
};