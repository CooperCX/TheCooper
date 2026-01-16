// 定义一个多重集合 S 的权值 val(S) 为 Mean(S)-Median(S)。

// 其中

// Mean(S)：S 所有数字的平均数
// Median(S)： S 的中位数，即若 S 从小到大排序为 s[0],s[1],...,s[k-1]，则中位数为 s[k/2]（除以2下取整）。
// Description
// 给定一个长度为 n 的非负整数序列 a[0],a[1],...,a[n-1]，对于所有 2^n 个子序列，求出最大权值的子序列的权值。

// Sample input
// n = 4 a = [1,2,5,9]

// Sample output
// 2

// Sample explanation
// 权值最大的子序列为 1,2,9

// 解题思路：1. 求出数组的所有子序列
//                 对于数组中的每一个元素，都存在选和不选两种情况，因此这一步的计算复杂度为2^n，利用这个思路使用二进制来处理
//         2. 计算每个子序列的val = Mean - Median，找到最大值
#include <algorithm>
#include <vector>

class calMaxValSolution {
   public:
    int calMaxVal(std::vector<int> values) {
        int maxVal = -1;
        int mask = 0;                    // 这是二进制的掩码
        int total = 1 << values.size();  // 这是二进制掩码的数量
        for (; mask < total; mask++) {
            std::vector<int> temp;
            bool isNullSub = true;
            for (int i = 0; i < values.size(); i++) {
                if (((1 << i) & mask) != 0) {
                    temp.push_back(values[i]);
                    isNullSub = false;
                }
            }
            if (!isNullSub) {
                std::sort(temp.begin(), temp.end());
                int mean = 0;
                for (const int& t : temp) {
                    mean += t;
                }
                int median = temp[temp.size() / 2];
                maxVal = std::max(mean / static_cast<int>(temp.size()) - median, maxVal);
            }
        }
        return maxVal;
    }

    // 高效解法：排序 + 前缀和 + 贪心 + 枚举中位数
    double calMaxVal(const std::vector<int>& values) {
        int n = values.size();
        if (0 == n) {
            return 0.0;
        }

        // 1. 排序
        std::sort(values.begin(), values.end());

        // 2. 前缀和，使用 long long 防止大数累加溢出
        std::vector<long long> prefix_sum(n + 1, 0);
        for (int i = 0; i < n; i++) {
            prefix_sum[i + 1] = prefix_sum[i] + values[i];
        }

        double max_val = 0.0;

        // 3. 枚举每一个元素作为子序列的中位数 a[i]
        for (int i = 0; i < n; i++) {
            int max_m = std::min(i, n - 1 - i);

            auto get_val = [&](int m) -> double {
                if (0 == m) {
                    return 0.0;
                }
                long long left_sum = prefix_sum[i + 1] - prefix_sum[i - m];
                long long right_sum = prefix_sum[n] - prefix_sum[n - m];
                double mean = static_cast<double>(left_sum + right_sum) / (2 * m + 1);

                return mean - values[i];
            };

            // get_val函数符合单峰特征，使用三分查找
            int l = 0, r = max_m;
            while (r - l > 2) {
                int m1 = l + (r - l) / 3;
                int m2 = r - (r - l) / 3;
                if (get_val(m1) > get_val(m2)) {
                    r = m2;
                } else {
                    l = m1;
                }
            }
            for (int m = l; m <= r; m++) {
                max_val = std::max(get_val(m), max_val);
            }
        }
        return max_val;
    }
};
