

inline int reachNumber(int target) {
    if (target < 0) target = -target;

    int numMoves = 0, sum = 0;
    while (sum < target || (sum - target) & 1) {
        numMoves++;
        sum += numMoves;
    }

    return numMoves;
}