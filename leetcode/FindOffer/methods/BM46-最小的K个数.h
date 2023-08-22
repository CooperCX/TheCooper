#include <vector>
#include <queue>
#include <functional>

class GetLeastNumbersSolution {
public:
    std::vector<int> GetLeastNumbers_Solution(std::vector<int> numbers, int k) {
        int n = numbers.size();
        std::vector<int> results;
        if (k > n) {
            return results;
        }
        std::priority_queue<int, std::vector<int>, std::greater<int>> pq;
        for (auto number : numbers) {
            pq.push(number);
        }
        while (k > 0) {
            results.push_back(pq.top());
            pq.pop();
            k--;
        }
        return results;
    }
};