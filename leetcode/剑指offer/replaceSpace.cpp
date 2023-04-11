/*
对于字符串的就地操作，字符串的长度需要改变，将多的字符长度放到最后，从后往前遍历
Hello_World
Hello_World__
Hello%20World
*/


class Solution {
public:
    void replaceSpace(char* str, int length) {
        int SpaceCount = 0;
        int TotalLength = length;
        for (int i = 0; i < length; i++) {
            if (str[i] == ' ') {
                SpaceCount++;
            }
        }
        TotalLength += SpaceCount * 2;
        for (int i = length - 1; i >= 0; i--) {
            if (str[i] != ' ') {
                str[--TotalLength] = str[i];
            } else {
                str[--TotalLength] = '0';
                str[--TotalLength] = '2';
                str[--TotalLength] = '%';
            }
        }
    }
};