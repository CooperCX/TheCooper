#include <vector>

// 找到油量最低点
inline int canCompleteCircuit(std::vector<int>& gas, std::vector<int>& cost) {
    int currentGas = 0, min_gas = 0, res = 0;
    for (int i = 0; i < gas.size(); ++i) {
        currentGas += gas[i] - cost[i];
        if (currentGas < min_gas) {
            min_gas = currentGas;
            res = i + 1;
        }
    }

    if (currentGas < 0) return -1;

    return res == gas.size() ? 0 : res;
}