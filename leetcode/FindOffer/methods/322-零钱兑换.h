#include <vector>

inline int coinChange(std::vector<int>& coins, int amount) {
    std::vector<long long> dp(amount + 1, INT_MAX);
    dp[0] = 0;

    for (int i = 1; i <= amount; ++i) {
        for (const int coin : coins) {
            if (i >= coin) {
                dp[i] = std::min(dp[i], dp[i - coin] + 1);
            }
        }
    }

    return (dp[amount] == INT_MAX ? -1 : dp[amount]);
}