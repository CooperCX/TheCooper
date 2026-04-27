#pragma once

#include <cmath>

namespace find_offer {

class Solution {
public:
    // 319. 灯泡开关
    // 分析：这道题看似是模拟，实际上是一个数论/数学题。
    // 第 i 个灯泡会被按多少次？取决于 i 有多少个正约数。
    // 只有按奇数次的灯泡最后才会亮着（因为初始是关的）。
    // 什么样的数有奇数个约数？只有【完全平方数】。
    // 例如：12 的约数有 1, 2, 3, 4, 6, 12（成对出现）。
    // 而 16 的约数有 1, 2, 4, 8, 16（4*4只算一个，所以是奇数个）。
    // 因此问题转化为：求 1 到 n 之间有多少个完全平方数。
    // 答案就是 sqrt(n) 向下取整。
    int bulbSwitch(int n) {
        // 强制转换为 int 类型，避免 warning 并实现截断（向下取整）
        return static_cast<int>(std::sqrt(n));
    }
};

} // namespace find_offer
