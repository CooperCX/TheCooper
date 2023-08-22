
class reverseIntSolution {
public:
    int reverseInt(int num) {
        int res = 0;
        while (num) {
            res = res * 10 + num % 10;
            num /= 10;
        }
        return res;
    }
};