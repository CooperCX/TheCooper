#include <vector>
#include <string>
#include <set>
class generatePermutationSolution {
public:
    std::vector<std::string> generatePermutation(std::string s) {
        // write code here
        std::vector<std::string> results;
        if (s == "") {
            results.push_back(s);
            return results;
        }
        int n = s.length();
        int total = 1 << n;
        int mask = 0;
        for (; mask < total; mask++) {
            std::string temp;
            for (int i = 0; i < n; i++) {
                if (((1 << i) & mask) != 0) {
                    temp += s[i];
                }
            }
            results.push_back(temp);
        }
        std::set<std::string> ss(results.begin(), results.end());
        results.assign(ss.begin(), ss.end());

        return results;
    }
};