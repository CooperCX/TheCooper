#include <string>

class compareVersionSolution {
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     * 比较版本号
     * @param version1 string字符串
     * @param version2 string字符串
     * @return int整型
     */
    int compare(std::string version1, std::string version2) {
        int len1 = version1.length();
        int len2 = version2.length();
        int i = 0, j = 0;
        while (i < len1 || j < len2) {
            long long num1 = 0;
            while (i < len1 && version1[i] != '.') {
                num1 = (version1[i] - '0') + num1 * 10;
                i++;
            }
            long long num2 = 0;
            while (j < len2 && version2[j] != '.') {
                num2 = (version2[j] - '0') + num2 * 10;
                j++;
            }
            if (num1 > num2) {
                return 1;
            } else if (num1 < num2) {
                return -1;
            } else {
                i++;
                j++;
            }
        }
        return 0;
    }
};