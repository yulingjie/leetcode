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
    int sign = 0;
    int beg = 0;
    for(;*c_ite != '\0'; ++c_ite)
    {        
        if(*c_ite == ' ')
        {
            if(beg == 1)
            {
                break;
            }
            continue;
        } 
        if(*c_ite == '-') 
        {
            if(sign != 0) break;
            sign = -1;
            if(beg == 1)
            {
                break;
            }
            beg = 1;
            continue;
        }
        if(*c_ite == '+')
        {
            if(sign != 0) break;
            sign = 1;
            if(beg == 1)
            {
                break;
            }
            beg = 1;
            continue;
        }

        if(!isCharNumber(*c_ite)) break;
        if(beg == 0) beg = 1;
        if(sign == 0) sign = 1;
        reverse_str[len] = *c_ite;
        ++len;        
    }
    if(sign == 0) sign = 1;
    reverse_str[len] = '\0';
    
    if(len <= 0) return 0;
    int rt = 0;
    int delta = 10;
    int lm = (sign >0) ? INT_MAX : INT_MIN;
    
    for(int i = 0; i < len; ++i)
    {
        int orig = rt;
        rt*= delta;
        if(rt / delta != orig) return lm;
        int n = c2i(reverse_str[i]) * sign;
        if(sign < 0 && ((lm - rt) > n)) return lm;
        if(sign > 0 && ((lm - rt) < n)) return lm;
        //if(sign * (lm - rt) < n) return lm;
        rt += n ;
    }
    free(reverse_str);
    reverse_str = NULL;
    return rt ;
}

int main(int argc,  char* argv[])
{
    char * str = "   0+1 42";
    int rt = str2int(str);
    printf("%d\n", rt);
}