#include <vector>

class FindNumbersWithSumSolution {
   public:
    // 务必使用 const & 传递数组！
    std::vector<int> FindNumbersWithSum(const std::vector<int>& array, int sum) {
        std::vector<int> result;
        int n = array.size();

        if (n < 2) {
            return result;
        }

        int start = 0, end = n - 1;
        while (start < end) {
            // 这里有个小细节：如果两个极大的证书相加，用 long long 可以防止溢出
            long long total = (long long)array[start] + array[end];

            if (total == sum) {
                // 写法优化：C++11 支持使用大括号初始化直接塞进结果
                return {array[start], array[end]};
            } else if (total > sum) {
                end--;
            } else {
                start++;
            }
        }

        return result;
    }
};
