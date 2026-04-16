#include <vector>
#include <queue>
#include <algorithm>

class GetLeastKNumbersSolution {
public:
    std::vector<int> Sort_Solution(std::vector<int> input, int k) {
        if (k > input.size()) {
            return std::vector<int>();
        }
        std::sort(input.begin(), input.end(), std::less<int>());
        return std::vector<int>({input.begin(), input.begin() + k});
    }

    std::vector<int> HeapSort_Solution(std::vector<int> input, int k) {
        std::vector<int> results;
        if (input.size() < k) {
            return results;
        }
        std::priority_queue<int, std::vector<int>, std::greater<int>> pq;
        for (int val : input) {
            pq.push(val);
        }
        while(k) {
            results.push_back(pq.top());
            pq.pop();
            k--;
        }
        return results;
    }

    std::vector<int> FastSort_Solution(std::vector<int> input, int k) {

    }
};