#include <vector>
#include <queue>

class Solution {
public:
    // 双指针
    std::vector<int> maxInWindows(const std::vector<int>& num, unsigned int size) {
        std::vector<int> results;
        int n = num.size();
        if (size == 0 || size > n) {
            return results;
        }
        int start = 0;
        while (start <= n - size) {
            int end = start + size - 1;
            int maxNum = num[start];
            while (end > start) {
                maxNum = std::max(num[end], maxNum);
                end--;
            }
            results.push_back(maxNum);
            start++;
        }
        return results;
    }

    // 借助优先队列
    std::vector<int> maxInWindows(const std::vector<int>& num, unsigned int size) {
        std::vector<int> results;
        int n = num.size(), count = 0;
        if (size == 0 || size > n) {
            return results;
        }
        std::priority_queue<int> q;
        for (int i = 0; i <= n - size; i++) {
            while (count < size) {
                q.push(num[i + count]);
                count++;
            }
            results.push_back(q.top());
            while (!q.empty()) {
                q.pop();
            }
            count = 0;
        }
        return results;
    }

    // 借助双端队列
    std::vector<int> maxInWindows(const std::vector<int>& num, unsigned int size) {
        std::vector<int> results;
        int n = num.size(), count = 0;
        if (size == 0 || size > n) {
            return results;
        }
        std::deque<int> q;
        for (int i = 0; i < n; i++) {
            while (!q.empty() && num[i] > num[q.back()]) {
                q.pop_back();
            }
            while (!q.empty() && (i - num[q.front()]) >= size) {
                q.pop_front();
            }
            q.push_back(i);
            if (i >= size - 1) {
                results.push_back(num[q.front()]);
            }
        }
        return results;
    }
};