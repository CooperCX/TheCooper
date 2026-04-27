#include <vector>

inline std::vector<int> productExceptSelf(std::vector<int>& nums) {
    std::vector<int> answer;
    if (nums.empty()) return answer;

    int n = nums.size();

    std::vector<int> left(n, 1);
    for (int i = 1; i < n; ++i) {
        left[i] = left[i - 1] * nums[i - 1];
    }

    std::vector<int> right(n, 1);
    for (int i = n - 2; i >= 0; --i) {
        right[i] = right[i + 1] * nums[i + 1];
    }

    for (int i = 0; i < n; ++i) {
        answer.push_back(left[i] * right[i]);
    }

    return answer;
}

// O(1) 额外空间版本：通过复用结果数组和动态维护后缀变量实现
inline std::vector<int> productExceptSelf2(std::vector<int>& nums) {
    int n = nums.size();
    if (n == 0) return {};
    // 1. 初始化结果数组，初始值设为 1
    std::vector<int> answer(n, 1);
    // 2. 第一遍遍历：计算前缀积
    // 让 answer[i] 存储 i 左侧所有元素的乘积
    // 此时 answer 充当了你之前代码中 left 数组的角色
    for (int i = 1; i < n; ++i) {
        answer[i] = answer[i - 1] * nums[i - 1];
    }
    // 3. 第二遍遍历：动态计算后缀积并合并结果
    // 使用一个变量 right 实时记录右侧累计的乘积
    // 此时它充当了你之前代码中 right 数组的角色，但只占用一个 int 的空间
    int right = 1;
    for (int i = n - 1; i >= 0; --i) {
        // 此时 answer[i] 已经是左积，乘以当前的右积即为最终结果
        answer[i] = answer[i] * right;
        // 更新右积，供下一个（左边的）位置使用
        right *= nums[i];
    }
    return answer;
}