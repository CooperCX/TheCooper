#include <vector>
#include <functional>
#include <queue>
class findKthSolution {
public:
    // 借助小顶堆
    int findKth(std::vector<int>& a, int n, int K) {
        std::priority_queue<int, std::vector<int>, std::greater<int>> q;
        for(auto num : a) {
            if (q.size() < K) {
                q.push(num);
            } else {
                if (num > q.top()) {
                    q.pop();
                    q.push(num);
                }
            }
        }

        return q.top();
    }

    // 快排思想
    int findKth(std::vector<int>& a, int n, int k) {
        int result = 0;
        partition(a, 0, n - 1, k, result);
        return result;
    }

private:
    void partition(std::vector<int>& a, int start, int end, int k, int& result) {
        if (start >= end) {
            result = a[start];
            return;
        }
        int pivot = a[start];
        int first = start, last = end;
        while (first < last) {
            while (first < last && a[last] < pivot) {
                last--;
            }
            if (first < last) {
                a[first++] = a[last];
            }
            while (first < last && a[first] > pivot) {
                first++;
            }
            if (first < last) {
                a[last--] = a[first];
            }
        }
        a[first] = pivot;
        if (first == k - 1) {
            result = a[first];
            return;
        } else if (first > k - 1) {
            partition(a, start, first - 1, k, result);
        } else {
            partition(a, first + 1, end, k, result);
        }
    }
};