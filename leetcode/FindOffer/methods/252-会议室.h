#include <algorithm>
#include <functional>
#include <map>
#include <queue>
#include <vector>

struct Interval {
    int start = 0;
    int end = 0;
};

inline bool canAttendAll(std::vector<Interval>& activities) {
    // 边界条件：没有活动或者只有1个活动时，必定能参加
    if (activities.empty()) return true;

    // 按照活动的开始时间升序排序
    std::sort(activities.begin(), activities.end(),
              [](const Interval& a, const Interval& b) { return a.start < b.start; });

    // 修复警告：使用 size_t 匹配 vector::size() 的返回类型
    for (size_t i = 1; i < activities.size(); ++i) {
        // 如果当前活动的开始时间 小于 上一个活动的结束时间，则必定冲突
        if (activities[i].start < activities[i - 1].end) return false;
    }

    return true;
}

inline int minHosts(std::vector<Interval>& activities) {
    if (activities.empty()) return 0;

    std::sort(activities.begin(), activities.end(),
              [](const Interval& a, const Interval& b) { return a.start < b.start; });

    std::priority_queue<int, std::vector<int>, std::greater<int>> heap;

    for (const Interval& act : activities) {
        if (!heap.empty() && heap.top() <= act.start) {
            heap.pop();
        }

        heap.push(act.end);
    }

    return heap.size();
}

inline int minHostsMapBased(const std::vector<Interval>& activities) {
    if (activities.empty()) return 0;

    std::map<int, int> timeline;

    for (const Interval& act : activities) {
        timeline[act.start]++;
        timeline[act.end]--;
    }

    int current_hosts = 0;
    int max_hosts = 0;

    for (const std::pair<int, int>& time : timeline) {
        current_hosts += time.second;
        max_hosts = std::max(max_hosts, current_hosts);
    }

    return max_hosts;
}