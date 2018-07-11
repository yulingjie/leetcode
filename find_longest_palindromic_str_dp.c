#include<stdio.h>
#include<stdlib.h>
#include <string.h>

int setLPSTable(int** ptable, int i, int j, char* in_str, int nlen, int * max_len, int * start_index)
{

    if(i > j) return -1;
    if(i >= nlen) return -1;
    if(j >= nlen) return -1;
    if(i < 0 || j < 0) return -1;
    if(ptable[i][j] != -1) return ptable[i][j];
    if(i == j)
    {
        ptable[i][j] = 1;
        if(*max_len < 1)
        {
            *max_len =1;
            *start_index = i;
        }
        return -1;    
    }

    int n = setLPSTable(ptable, i+1, j -1, in_str, nlen, max_len, start_index);
    if(n != 0
    && (in_str[i] == in_str[j]))
    {        
        ptable[i][j] =1;
        int len = j - i +1;
        if(*max_len < len)
        {
            *max_len = len;
            *start_index = i;
        }
    }
    else
    {
        ptable[i][j] = 0;
    }        
    setLPSTable(ptable, i, j-1, in_str, nlen, max_len, start_index);
    setLPSTable(ptable, i + 1, j, in_str, nlen, max_len, start_index);
}
char* findLPSDP(char in_str[])   
{
    int nlen = strlen(in_str);
    int ** parr = (int**)malloc(sizeof(int*)* nlen);
    for(int i = 0; i < nlen; ++i)
    {
        parr[i] = (int*)malloc(sizeof(int) * nlen);
    }

    for(int i = 0; i < nlen; ++i)
    {
        for(int j = 0; j < nlen; ++j)
        {
            parr[i][j] = -1;
        }
    }
    int max_len = 0;
    int start_index = 0;
    setLPSTable(parr,0,nlen -1,in_str, nlen, & max_len, & start_index);
    char* rt_str = (char*)malloc((sizeof(char) + 1)* max_len);
    printf("startindex %d, max len %d\n", start_index, max_len);
    for(int i = 0; i < (max_len); ++i)
    {
        printf("%c", in_str[start_index + i]);
        rt_str[i] = in_str[start_index + i];
    }
    rt_str[max_len] = '\0';
    printf("\n");

   /* for(int i = 0; i < nlen; ++i)
    {
        for(int j = 0; j < nlen; ++j)
        {
            if(parr[i][j] >= 0) printf(" ");
            printf("%d ", parr[i][j]);
        }
        printf("\n");
    }*/

    for(int i = 0; i < nlen; ++i)
    {        
       free(parr[i]);        
    }
    free(parr);
    return rt_str;
}

int main (int argc, char* argv[])
{
    char in_str[] = "cabbaabb";
    findLPSDP(in_str);
}