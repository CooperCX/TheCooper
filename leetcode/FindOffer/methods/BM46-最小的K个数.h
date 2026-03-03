#include <functional>
#include <queue>
#include <vector>

class GetLeastNumbersSolution {
   public:
    std::vector<int> GetLeastNumbers_Solution(const std::vector<int> numbers, int k) {
        std::vector<int> results;
        int n = numbers.size();
        if (0 == n || k <= 0) return results;
        if (k >= n) {
            results = numbers;
            return results;
        }

        std::priority_queue<int> max_heap;
        for (int i = 0; i < n; i++) {
            if (max_heap.size() < k) {
                max_heap.push(numbers[i]);
            } else {
                if (numbers[i] < max_heap.top()) {
                    max_heap.pop();
                    max_heap.push(numbers[i]);
                }
            }
        }

        while (!max_heap.empty()) {
            results.push_back(max_heap.top());
            max_heap.pop();
        }

        return results;
    }
};