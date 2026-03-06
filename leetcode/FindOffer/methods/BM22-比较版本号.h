#include <string>

class compareVersionSolution {
   public:
    // 解法：双指针单层遍历，流式解析比较
    // 时间复杂度 O(max(N, M))，空间复杂度 O(1)
    int compare(std::string version1, std::string version2) {
        int len1 = version1.length();
        int len2 = version2.length();

        // 双指针，分别在两个版本号上推进
        int i = 0, j = 0;

        // 只要还有人没走到头，就继续比较
        // 遇到短的版本号先走完，会在这一轮天然获得 v = 0，完美契合缺省默认为 0 的规则
        while (i < len1 || j < len2) {
            // 提取 version1 当前小节的数字 (用 long long 防超长整型溢出)
            long long v1 = 0;
            // 一直读数字，直到遇到 '.' 或者读到尽头
            while (i < len1 && version1[i] != '.') {
                v1 = v1 * 10 + (version1[i] - '0');
                i++;
            }

            // 提取 version2 当前小节的数字
            long long v2 = 0;
            while (j < len2 && version2[j] != '.') {
                v2 = v2 * 10 + (version2[j] - '0');
                j++;
            }

            // 如果当前小节分出了胜负，直接结算出局
            if (v1 > v2) return 1;
            if (v1 < v2) return -1;

            // 既然当前小节打平 (也就是 v1 == v2)
            // 准备跨过分界符 '.' 开启下一小节的比拼
            // 需要判断的原因是：指针有可能因为到尾部了才退出的内层循环，此时并没点。
            if (i < len1) i++;
            if (j < len2) j++;
        }

        // 全部小节比完都是平局
        return 0;
    }
};
