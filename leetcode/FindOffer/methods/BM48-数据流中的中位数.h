#include <queue>

// 借助大小顶堆
class MedianFinder {
   public:
    MedianFinder() {}

    void addNum(int num) {
        count++;
        if (count & 1) {
            right_min_heap.push(num);
            left_max_heap.push(right_min_heap.top());
            right_min_heap.pop();
        } else {
            left_max_heap.push(num);
            right_min_heap.push(left_max_heap.top());
            left_max_heap.pop();
        }
    }

    double findMedian() {
        if (count & 1) return left_max_heap.top();
        return (left_max_heap.top() + right_min_heap.top()) / 2.0;
    }

   private:
    int count = 0;
    std::priority_queue<int, std::vector<int>, std::less<int>> left_max_heap;
    std::priority_queue<int, std::vector<int>, std::greater<int>> right_min_heap;
};