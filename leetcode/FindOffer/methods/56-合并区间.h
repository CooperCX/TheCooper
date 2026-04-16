#include <algorithm>
#include <vector>
inline std::vector<std::vector<int>> merge(std::vector<std::vector<int>>& intervals) {
    if (intervals.empty()) return {};

    std::sort(intervals.begin(), intervals.end(),
              [](const std::vector<int>& a, const std::vector<int>& b) { return a[0] < b[0]; });

    std::vector<std::vector<int>> results;
    results.push_back(intervals[0]);

    for (int i = 1; i < intervals.size(); ++i) {
        if (intervals[i][0] <= results.back()[1]) {
            results.back()[1] = std::max(results.back()[1], intervals[i][1]);
        } else {
            results.push_back(intervals[i]);
        }
    }

    return results;
}