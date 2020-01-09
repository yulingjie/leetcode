#include <cstdio>
#include <iostream>
#include <string>
using std::string;
using std::cout;
using std::endl;
class Solution{
    public:
        // prefix tree
        int strStr(string haystack, string needle)
        {
            return -1;
        }
        //
        //     -____-
        // ____-____-____________________
        //
        int strStr1(string haystack, string needle)
        {
            if(needle.length() == 0) return 0;
            if(needle.length() > haystack.length()) return -1;
            int needle_len = needle.length();
            int startIndex = 0;
            int endIndex = haystack.length() -1;
            for(; startIndex <= endIndex;)
            {
                if (haystack[startIndex] != needle[0])
                {
                    startIndex ++;
                    continue;
                }
                int iter = startIndex;
                bool firstMatch = true;
                for(int i = 0; i != needle_len ; ++iter, ++i)
                {
                    if (iter >= endIndex)
                    {
                        firstMatch = false;
                        break;
                    }
                    if (haystack[iter] != needle[i])
                    {
                        firstMatch = false;
                        break;
                    }
                }
                if(firstMatch)
                {
                    return startIndex;
                }
                else
                {
                    startIndex = iter;
                }
            }
            return -1;
        }
};
int main(int argc, char *argv[])
{
    if(argc < 3)
    {
        cout<<"usage haystack needle"<<endl;
        return -1;
    }
    string haystack = argv[1];
    string needle = argv[2];
    Solution s;
    int rt = s.strStr(haystack,needle);
    cout<<"result = "<<rt<<endl;
    return 0;
}
