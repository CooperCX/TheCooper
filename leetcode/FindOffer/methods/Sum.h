
class SumOfOneToNSolution {
public:
    // 位运算
    int AddTwoNumberWithoutPlus(int num1, int num2) {
        while (num2) {
            int a = num1 ^ num2;
            int b = (num1 & num2) << 1;
            num1 = a;
            num2 = b;
        }
        return num1;
    }

    // 借助数据结构大小
    int SumOfOneToN(int n) {
        bool a[n][n + 1];
        return sizeof(a);
    }

    // 借助&&的判断顺序
    int SumOfOneToN(int n) {
        int sum = n;
        bool ans = (n > 0) && (sum += SumOfOneToN(n - 1) > 0);
        return sum;
    }
};