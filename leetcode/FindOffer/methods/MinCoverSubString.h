#include <string>
#include <unordered_map>

class MinCoverSubStringSolution {
public:
    // 滑动窗口法，一般借用双指针实现
    std::string MoveWindow(const std::string& S, const std::string& T) {
        if (S == "" || T == "" || T.length() > S.length()) {
            return "";
        }
        std::unordered_map<char, int> hash;
        for (int i = 0; i < T.length(); i++) {
            hash[T[i]]--;
        }
        int cnt = S.length() + 1;
        int slow = 0, fast = 0;
        int left = -1, right = -1;
        for (;fast < S.length(); fast++) {
            if (hash.count(S[fast])) {
                hash[S[fast]]++;
            }
            while (check(hash)) {
                if (cnt > fast - slow + 1) {
                    cnt = fast - slow + 1;
                    left = slow;
                    right = fast;
                }
                if (hash.count(S[slow])) {
                    hash[S[slow]]--;
                }
                slow++;
            }
        }
        if (left == -1) {
            return "";
        }
        return std::string(S.begin() + left, S.begin() + right + 1);
    }
private:
    bool check(const std::unordered_map<char, int>& hash) {
        for (auto it = hash.begin(); it != hash.end(); it++) {
            if (it->second < 0) {
                return false;
            }
        }
        return true;
    }
};