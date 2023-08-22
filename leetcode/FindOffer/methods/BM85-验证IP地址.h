#include <vector>
#include <string>

class Solution {
  public:
    //将字符串从.或者:分割开
    std::vector<std::string> split(std::string s, std::string spliter) {
        std::vector<std::string> res;
        int i;
        //遍历字符串查找spliter
        while ((i = s.find(spliter)) && i != s.npos) {
            //将分割的部分加入vector中
            res.push_back(s.substr(0, i));
            s = s.substr(i + 1);
        }
        res.push_back(s);
        return res;
    }
    bool isIPv4 (std::string IP) {
        std::vector<std::string> s = split(IP, ".");
        //IPv4必定为4组
        if (s.size() != 4)
            return false;
        for (int i = 0; i < s.size(); i++) {
            //不可缺省，有一个分割为零，说明两个点相连
            if (s[i].size() == 0)
                return false;
            //比较数字位数及不为零时不能有前缀零
            if (s[i].size() < 0 || s[i].size() > 3 || (s[i][0] == '0' && s[i].size() != 1))
                return false;
            //遍历每个分割字符串，必须为数字
            for (int j = 0; j < s[i].size(); j++)
                if (!isdigit(s[i][j]))
                    return false;
            //转化为数字比较，0-255之间
            int num = stoi(s[i]);
            if (num < 0 || num > 255)
                return false;
        }
        return true;
    }
    bool isIPv6 (std::string IP) {
        std::vector<std::string> s = split(IP, ":");
        //IPv6必定为8组
        if (s.size() != 8)
            return false;
        for (int i = 0; i < s.size(); i++) {
            //每个分割不能缺省，不能超过4位
            if (s[i].size() == 0 || s[i].size() > 4)
                return false;
            for (int j = 0; j < s[i].size(); j++) {
                //不能出现a-fA-F以外的大小写字符
                if (!(isdigit(s[i][j]) || (s[i][j] >= 'a' && s[i][j] <= 'f') ||
                        (s[i][j] >= 'A' && s[i][j] <= 'F')))
                    return false;
            }
        }
        return true;
    }
    std::string solve(std::string IP) {
        if (IP.size() == 0)
            return "Neither";
        if (isIPv4(IP))
            return "IPv4";
        else if (isIPv6(IP))
            return "IPv6";
        return "Neither";
    }
};
