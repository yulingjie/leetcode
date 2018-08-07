#include <string.h>
#include<stdlib.h>
#include <stdio.h>


char* longestCommonPrefix(char** strs, int strsSize) {
    
    if(strs == NULL) return NULL;
    
    char pite = '\0';
    int index = 0;
    int next = 1;
    while(next)
    {        
        for(int i = 0;i != strsSize; ++i)
        {
            if(strs[i][index] == '\0')
            {
                next = 0;
                break;
            }
            if(pite == '\0')
            {                
                pite = strs[i][index];
                continue;
            }
            if(pite != strs[i][index])
            {
                next = 0;
                break;
            }            
        }   
        if(!next) break;
        ++index; 
        pite = '\0';
    }
    if(index <= 0) return NULL;
    char * s = strs[0];
    
    char* rt = (char*)malloc(sizeof(char)*(index + 1));
    for(int i =0; i < index; ++i)
    {
        rt[i] = s[i];
    }
    rt[index] = '\0';
    return rt;
    
}

int main(int argc, char* argv[])
{
    char** strs = (char**)malloc(sizeof(char*) * 3);
    strs[0] = "flower";
    strs[1] = "flow";
    strs[2] = "flight";
    
    char** p = strs;
    printf("%s\n", p[0]);
    char* ss =longestCommonPrefix((char**)strs, 3);
    printf("%s\n", ss);
}