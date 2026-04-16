#include <algorithm>  // 不要忘记包含
#include <string>
#include <vector>

class PrintMinNumberSolution {
   public:
    // 【优化 1】：绝对使用 const & 传递只读大对象
    std::string PrintMinNumber(const std::vector<int>& numbers) {
        if (numbers.empty()) return "";

        std::vector<std::string> temp;
        // 最好给 vector 预分配空间，进一步压榨性能
        temp.reserve(numbers.size());

        for (int number : numbers) {
            temp.push_back(std::to_string(number));
        }

        // 【优化 2】：Lambda 表达式的高频比较参数，必须使用 const & !!!
        std::sort(temp.begin(), temp.end(), [](const std::string& a, const std::string& b) {
            // 如果求最小数改为 < ，求最大数用 >
            return a + b > b + a;
        });

        // 【优化 3】：前置拦截 LeetCode 专属 [0, 0] 陷阱
        // 如果排序后最大的数字开头都是 "0"，那后面全是 "0"，直接返回 "0" 即可
        if (temp[0] == "0") {
            return "0";
        }

        std::string result;
        // 【优化 4】：for 循环不拷贝，只用只读引用读取字符串
        for (const auto& t : temp) {
            result += t;
        }

        return result;
    }
};
