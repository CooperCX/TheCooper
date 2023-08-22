#include <queue>

// 借助大小顶堆
class GetMedianSolution {
public:
    void Insert(int num) {
        count++;
        if (count & 1) {
            small.push(num);
            big.push(small.top());
            small.pop();
        } else {
            big.push(num);
            small.push(big.top());
            big.pop();
        }
    }

    double GetMedian() {
        if (count & 1) {
            return big.top();
        } else {
            return (big.top() + small.top()) / 2.0;
        }
    }
private:
    int count = 0;
    std::priority_queue<int, std::vector<int>, std::less<int>> big;
    std::priority_queue<int, std::vector<int>, std::greater<int>> small;
};