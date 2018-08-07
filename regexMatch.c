#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int matchhere(char* pite, char* in_str);
/*
'.' Matches any single character.
'*' Matches zero or more of the preceding element.
The matching should cover the entire input string (not partial).
*/

int matchstar(char c, char* pite, char * in_str)
{    
    char* site = in_str;
    for(;(*site != '\0') && ((c== '.') || (c == (*site))); ++site);
    for(; site != in_str-1; -- site)
    {
        if(matchhere(pite, site)) return 1;
    }
    return 0;
}

int matchhere(char* pite, char* in_str)
{
    if((*pite == '\0') &&(*in_str == '\0')) return 1;
    if(*pite == '\0') return 0;     
    if(pite[1] == '*') return matchstar(*pite, pite + 2, in_str);
    if((*in_str != '\0') && (*pite == *in_str ||*pite == '.') ) return matchhere(pite +1, in_str + 1);
    return 0;
}


int match(char* in_str, char* pattern)
{
    return matchhere(pattern, in_str);
}


int main(int argc, char* argv[])
{
    int rt = match("","..*");
    printf("result %s\n", rt ? "true": "false");
}
