#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int min(int a,int b)
{
    if(a > b) return b;
    return a;
}


char* findLPS(char* in_str)
{
    int nsize = strlen(in_str);
    char* process_str = (char*)malloc(sizeof(char)* (2* nsize + 2));
    for(int i = 0; i < (2*nsize + 1); ++i)
    {
        if(i %2 == 0)
        {
            process_str[i]='#';
        }
        else
        {
            process_str[i] = in_str[i/2];
        }
    }
    process_str[2*nsize + 1]= '\0';

    int n = 2*nsize + 1;
   
    int *p = (int*)malloc(sizeof(int)* n);

    int center = 0, right = 0;
    for(int i = 1; i < n - 1; ++i)
    {
        int i_mirror = 2 * center - i;
        p[i] = (right > i) ? min(right -i, p[i_mirror]) : 0;

        while(
            (i + 1 + p[i] < n) && (i - 1 -p[i] >= 0) &&
            (process_str[i + 1 + p[i]] == process_str[i - 1 - p[i]]))
        {
            ++ p[i];
        }
        if(i + p[i] > right)
        {
            center = i;
            right = i + p[i];
        }
    }

    int maxLen = 0;
    int centerIndex = 0;
    for(int i = 1; i < n-1; ++i)
    {
        printf("%d ", p[i]);
        if(p[i] > maxLen)
        {
            maxLen = p[i];
            centerIndex = i;
        }
    }
    int len = maxLen;
    char* prt= (char* )malloc(sizeof(char)* (len + 1));

    int j = 0;
    for(int i = centerIndex - maxLen; i < centerIndex + maxLen; ++i)
    {
        if(i %2 ==1)
        {
            prt[j] = process_str[i];
            ++ j;
        }
    }
    prt[len] = '\0';
    
    free(process_str);
    free(p);
    return prt;
}

int main(int argc, char* argv[])
{
    char in_str[] = "babad";
    char * prt = findLPS(in_str);
    printf("%s", prt);

}