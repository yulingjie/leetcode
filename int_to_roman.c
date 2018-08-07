#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include "util.h"
/*
I             1
V             5
X             10
L             50
C             100
D             500
M             1000
*/

char* toThousandRadix(int num)
{
    int n = num / 1000;
    char* rt = (char*)malloc(sizeof(char) * (n + 1));
    for(int i = 0; i < n; ++i)
    {
        rt[i]= 'M';
    }
    rt[n] = '\0';
    return rt;
}

char* toDecimalRadix(int num, char TC, char VC, char IC)
{
    char* rt = NULL;
    if(num >= 9)
    {
        rt = (char*)malloc(sizeof(char)*3);
        rt[0] = IC;
        rt[1] = TC;
        rt[2] = '\0';
    }
    else if(num >=5)
    {
        int r = num - 5;        
        rt = (char*)malloc(sizeof(char)* (r+ 2));
        rt[0] = VC;
        for(int i = 0; i < r; ++i)
        {
            rt[i + 1] = IC;
        }
        rt[r + 1] = '\0';
    }
    else if(num >= 4)
    {
        rt =(char*)malloc(sizeof(char)* 3);
        rt[0]= IC;
        rt[1] = VC;
        rt[2] = '\0';
    }
    else if(num > 0)
    {
        int r = num;
        rt= (char*)malloc(sizeof(char) * (num + 1));
        for(int i = 0; i < r; ++i)
        {
            rt[i] = IC;
        }
        rt[num] = '\0';
    }
    return rt;
}
char* toHundredRadix(int num)
{
    num %= 1000;
    return toDecimalRadix(num / 100, 'M', 'D', 'C');
}
char* toTenRadix(int num)
{
    num %= 100;
    return toDecimalRadix(num/10, 'C', 'L','X');
}
char* toOneRadix(int num)
{
    num %= 10;
    return toDecimalRadix(num, 'X','V', 'I');
}
char* toRoman(int num)
{
    if(num <=0) return NULL;
    char* rt_str = NULL;
    int remain = 0;
    if(num >= 1000)
    {
        int t = num / 1000 * 1000;
        remain = num - t;
        rt_str = toThousandRadix(t);        
    }
    else if(num >= 100)
    {
        int h = num / 100 * 100;
        remain = num - h;
        rt_str = toHundredRadix(h);
    }
    else if(num >= 10)
    {
        int t = num/ 10 * 10;
        remain = num - t;
        rt_str = toTenRadix(t);
    }
    else 
    {
        rt_str = toOneRadix(num);
    }
    char* remain_str = toRoman(remain);
    int remainCount = remain_str != NULL ? strlen(remain_str): 0;
    int rtCount = rt_str != NULL ? strlen(rt_str) : 0 ;
    char* str = (char*)malloc(sizeof(char)* (rtCount+ remainCount + 1));
    if(rt_str != NULL)
    {
        memcpy(str,rt_str, rtCount);
    }
    if(remain_str != NULL)
    {
        memcpy(str + rtCount, remain_str, remainCount);
    }
    str[rtCount+ remainCount] = '\0';
    free(remain_str);
    free(rt_str);
    return str;
}

char* intToRoman(int num)
{   
    int INDEX[] = {1000, 500, 100, 50, 10, 5};

   
}

int main(int argc, char* argv[])
{
    int i = str2int(argv[1]);
    char* rt = toRoman(i);
    printf("%s\n", rt);
    free(rt);
}