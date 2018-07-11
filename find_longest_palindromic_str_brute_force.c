#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int isSubstringPalindromic(char in_str[], int start, int end)
{
    if(end < start) return 0;
    if(start < 0 || end >= strlen(in_str)) return 0;
    int length = (end - start + 1) /2;
    for(int i = 0; i <= length; ++i)
    {
        int startIndex = i + start;
        int endIndex = end - i;
        if(in_str[startIndex]!= in_str[endIndex]) return 0;
    }
    return 1;
}

void findLRPBruteForce(char in_str[])
{
    int len = strlen(in_str);
    int startIndex = 0;
    int endIndex = 0;
    int maxLen = 0;
    int maxStartIndex =0 ;
    int maxEndIndex = 0;
    for(endIndex = 0; endIndex < len; ++endIndex)
    {
        for(startIndex = 0; startIndex <= endIndex; ++startIndex)
        {
            if(isSubstringPalindromic(in_str,startIndex, endIndex))
            {
                int curLen = endIndex - startIndex + 1;
                if(curLen > maxLen)
                {
                    maxLen = curLen;
                    maxStartIndex = startIndex;
                    maxEndIndex = endIndex;
                }
            }
        }
    }
    if(maxLen < 0)
    {
        printf("not lrp\n");
        return ;
    }
    printf("max str: ");
    int p = 0;
    for(p = maxStartIndex; p <= maxEndIndex; ++p)
    {
        printf("%c", in_str[p]);
    }
    printf("\n");
}

int main(int argc, char* argv[])
{
    char str[] = "forgeeksskeegfor";
    findLRPBruteForce(str);
}