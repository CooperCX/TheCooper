#include <deque>
#include <vector>

class maxInWindowsSolution {
   public:
    // 借助双端队列
    std::vector<int> maxInWindows(const std::vector<int>& nums, unsigned int size) {
        std::vector<int> results;

        int n = nums.size();
        if (0 == n || size > n) return results;

        std::deque<int> q;

        for (int i = 0; i < n; i++) {
            while (!q.empty() && nums[i] > nums[q.back()]) q.pop_back();

            q.push_back(i);

            if (i - q.front() >= size) q.pop_front();

            if (i >= size - 1) results.push_back(nums[q.front()]);
        }

        return results;
    }
};