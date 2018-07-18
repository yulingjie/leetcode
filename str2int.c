#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
int isCharNumber(char c)
{
    return ((int)c >= (int)'0') && ((int)c <= (int)'9');
}
int c2i(char c)
{
    return ((int)c) - ((int)'0');
}
int str2int(char* in_str)
{
    char* reverse_str = (char*)malloc(sizeof(char) *(strlen(in_str) + 1));
    memset(reverse_str, '\0', strlen(in_str) + 1);
    char* c_ite = in_str;
    int len = 0;
    int sign = 1;
    while(*c_ite != '\0')
    {        
        if(*c_ite == ' ') continue;
        if(*c_ite == '-') sign = -1;
        if(!isCharNumber(*c_ite)) return 0;
        reverse_str[len] = *c_ite;
        ++len;
    }
    if(len <= 0) return 0;
    int rt = 0;
    int delta = 10 * sign;
    int lm = sign ? INT_MAX : INT_MIN;
    for(int i = 0; i < len; ++i)
    {
        int orig = rt;
        rt*= delta;
        if(rt / delta != orig) return 0;
        int n = c2i(reverse_str[i]);
        if(sign * (lm - rt) < n) return 0;
        rt += (sign * n);
    }
    free(reverse_str);
    reverse_str = NULL;
    return rt;
}

int main(int argc,  char* argv[])
{
    
}