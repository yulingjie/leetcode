#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#define SUFFIX_FORWARD_REVERSE

#include"suffixTree.h"



void setIndiceDFS(SuffixTreeNode* node,int str_size)
{
    if(node== NULL) return;

   
        node->pforwardIndices = (int*)malloc(sizeof(int)* (str_size + 1));
    
    
        node->preverseIndices = (int*)malloc(sizeof(int) * (str_size + 1));
    
    
    if(node->suffixIndex > -1)
    {
        


        if(node->suffixIndex <= str_size)
        {
            node->pforwardIndices[node->suffixIndex] = 1;                       
        }
        else 
        {
            node->preverseIndices[node->suffixIndex - str_size -1] = 1;            
        }        
    }
    else
    {        
             
            
        for(int i = 0; i < MAX_CHAR; ++i)
        {
            if(node->children[i] == NULL) continue;
         
            setIndiceDFS(node->children[i], str_size);
            for(int j = 0; j < str_size +  1; ++j)
            {
                if(node->children[i]->pforwardIndices[j] != 1)
                {
                    continue;
                }                
                node->pforwardIndices[j] = 1;
            }
            
            for(int j = 0; j< str_size + 1; ++j)
            {
                if(node->children[i]->preverseIndices[j] != 1) continue;
                node->preverseIndices[j] = 1;
            }         
        }
       
    }
}
void freeNodeDPS(SuffixTreeNode* node)
{
    if(node == NULL) return;
    if(node->pforwardIndices !=NULL)
    {
        free(node->pforwardIndices);
        node->pforwardIndices = NULL;
    }
    if(node->preverseIndices != NULL)
    {
        free(node->preverseIndices);
        node->preverseIndices = NULL;
    }

    if(node->suffixIndex == -1)
    {
        for(int i = 0; i < MAX_CHAR; ++i)
        {
            if(node->children[i] == NULL) continue;
            freeNodeDPS(node->children[i]);
        }
    }
}

void findLPSDFS(SuffixTreeNode* node, int cur_depth, int str_size,int* max_depth, int * start_index)
{
    if(node == NULL) return;

    if(node->suffixIndex == -1)
    {
        if(cur_depth > (*max_depth)
        && node->pforwardIndices != NULL 
        && node->preverseIndices != NULL)
        {
            for(int i =0; i < str_size; ++i)
            {
                if(node->pforwardIndices[i] == 0) continue;
                int reverse_index = str_size -1 - (i + cur_depth -1);
                if(node->preverseIndices[reverse_index] == 1)
                {
                    if(cur_depth > (*max_depth))
                    {
                        *max_depth = cur_depth;
                        *start_index = i;
                    }
                    break;
                }
            }
        }
        

        for(int i = 0; i < MAX_CHAR; ++i)
        {
            if(node->children[i] == NULL) continue;
            findLPSDFS(node->children[i], cur_depth + GetEdgeLength(node->children[i]), str_size, max_depth, start_index);
        }
    }    
}
void findLPS(char str[])
{
    char* str_palin = (char*)malloc(sizeof(char)* (strlen(str) * 2 + 2));

    for(int i= 0; i < strlen(str); ++i)
    {
        str_palin[i] = str[i];
        str_palin[strlen(str) * 2 -i ] = str[i];
    }
    str_palin[strlen(str)] = '#';
    str_palin[strlen(str) * 2 + 1] = '$';
    SuffixTreeNode* node = SuffixTreeConstruct(str_palin);
    
    setIndiceDFS(node, strlen(str));
   
    int cur_depth = 0;
    int max_depth = 0;
    int start_index = 0;
    findLPSDFS(node, cur_depth, strlen(str), &max_depth, & start_index);
    printf("max depth %d, start index %d\n",max_depth, start_index);
    for(int i = 0; i < max_depth; ++i)
    {
        printf("%c", str[i + start_index]);
    }
    printf("\n");
    freeNodeDPS(node);
}




int main(int argc, char* argv[])
{
    char str[] = "forgeeksskeegfor";
    findLPS(str);
}


