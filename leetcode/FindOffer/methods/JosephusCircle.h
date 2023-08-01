

class JosephusCircleSolution {
public:
    int JosephusCircle(int n, int m) {
        if (n <= 0 || m <= 0) {
            return -1;
        }
        int ans = 0;
        for (int i = 2; i <= n; i++) {
            ans = (ans + m) % i;
        }
        return ans;
    }

    int JosephusCircle(int n, int m) {
        if (n == 0) {
            return -1;
        }
        if (n == 1) {
            return 0;
        }

        return (m + JosephusCircle(n - 1, m)) % n;
    }
};