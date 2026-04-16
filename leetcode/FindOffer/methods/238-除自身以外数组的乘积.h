#include <vector>

class multiplyVectorSolution {
public:
    std::vector<int> multiply(const std::vector<int>& A) {
        int n = A.size();
        std::vector<int> B(n , 1);
        int temp = 1;
        for (int i = 0; i < n; temp *= A[i], i++) {
            B[i] = temp;
        }
        temp = 1;
        for(int i = n - 1; i >= 0; temp *= A[i], i--) {
            B[i] *= temp;
        }
        return B;
    }
};