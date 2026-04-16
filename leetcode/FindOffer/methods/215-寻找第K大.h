/*
    寻找第 K 大的元素 (Top K 问题)
    解法 1：小顶堆 (适合海量数据/数据流，空间 O(K))
    解法 2：快速选择 Quick Select (适合静态数组，时间 O(N))
*/
#include <functional>  // std::greater
#include <queue>
#include <vector>
class findKthSolution {
   public:
    // ==========================================
    // 解法 1：借助小顶堆 (Min Heap)
    // 逻辑原理：求最大的 K，建小顶堆。堆顶是这 K 个霸主里最弱的守门员。
    // 时间 O(N log K)，空间 O(K)
    // ==========================================
    int findKth1(std::vector<int>& a, int n, int K) {
        // C++ 声明小顶堆的标配写法
        std::priority_queue<int, std::vector<int>, std::greater<int>> q;

        for (auto num : a) {
            // 前 K 个人先占满坑位
            if (q.size() < K) {
                q.push(num);
            }
            // 坑位满了，开启守门员挑战赛
            else {
                // 如果外面的挑战者比守门员（当前 K 个最大值里的那个最小值）还要大
                if (num > q.top()) {
                    q.pop();      // 守门员惨遭淘汰
                    q.push(num);  // 挑战者上位入盟
                }
            }
        }
        // 历经大浪淘沙，最后留在堆里的就是全天下最大的 K 个人。
        // 而站在堆顶的那个，刚好就是第 K 大！
        return q.top();
    }
    // ==========================================
    // 解法 2：基于快速排序的快速选择算法 (Quick Select)
    // 逻辑原理：利用快排 partition，每次能排除一半的死胡同
    // 均摊时间 O(N)，最坏 O(N^2)，空间 O(log N) (递归栈)
    // ==========================================
    int findKth2(std::vector<int>& a, int n, int k) {
        int result = 0;
        // 把整个数组扔进去，告诉它：从大到小排，我要找下标为 k-1 的那个人！
        partition(a, 0, n - 1, k, result);
        return result;
    }

   private:
    void partition(std::vector<int>& a, int start, int end, int k, int& result) {
        // 【防御】越界触底
        if (start >= end) {
            // 因为题目保证一定有答案，所以一旦区间缩到只有一个人，那肯定是他
            result = a[start];
            return;
        }
        // 经典快排：挖坑填数法 (从大到小降序排列)
        int pivot = a[start];  // 把起始兵力提拔为基准数，原地留下一个“坑”
        int first = start, last = end;
        while (first < last) {
            // 1. 从右往左扫，找比基准数【大】的数 (因为我们要找第 K 大，必须降序排)
            while (first < last && a[last] < pivot) {
                last--;  // 这个数比基准小，很安分，继续向左下探
            }
            if (first < last) {
                a[first++] = a[last];  // 找到了个刺头比基准还大的，把它填到左边的坑里去
            }
            // 2. 从左往右扫，找比基准数【小】的数
            while (first < last && a[first] > pivot) {
                first++;  // 这个数比基准大，很安分，向右下探
            }
            if (first < last) {
                a[last--] = a[first];  // 把这个太小的数，填到刚才右边挖出来的那个坑里去
            }
        }

        // 最后 left == right 会师交汇，把一开始的基准数填回最后一个坑
        a[first] = pivot;
        // 【最核心的 Quick Select 剪枝】
        // 基准数归位后的这个下标 first，就是它在彻底排完序后绝对不可撼动的位置！
        if (first == k - 1) {
            // 太幸运了，这一刀刚好切在了第 K 大的位置上！
            result = a[first];
            return;
        } else if (first > k - 1) {
            // 基准数的位置偏右了，说明我们要找的那个更厉害的人，在基准数的左边阵营里！
            // 把右边那些弱兵全扔了，只带着左半边去递归！(此乃降维打击 O(N) 的关键)
            partition(a, start, first - 1, k, result);
        } else {
            // 基准数太菜，卡位偏左了，我们要找的目标在它的右边阵营里
            partition(a, first + 1, end, k, result);
        }
    }
};