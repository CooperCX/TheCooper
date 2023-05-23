#include <stack>
#include <vector>

bool IsPopOrder(std::vector<int> pushV, std::vector<int> popV) {
    if (pushV.empty() || popV.empty() || pushV.size() != popV.size()) {
        return false;
    }
    int n = pushV.size();
    int popIndex = 0;
    std::stack<int> s;
    for (int i = 0; i < n; i++) {
        s.push(pushV[i]);
        while (!s.empty() && s.top() == popV[popIndex]) {
            s.pop();
            popIndex++;
        }
    }
    return s.empty();
}