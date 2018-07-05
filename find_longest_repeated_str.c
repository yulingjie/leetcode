#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "suffixTree.h"

void find_deepest_node(SuffixTreeNode* node,int label_height, int * pmax_height,int * start_index)
{
    if(node == NULL) return;
    if(node->suffixIndex != -1) 
    {
        if(label_height - GetEdgeLength(node) > *pmax_height)
        {
            *pmax_height = label_height - GetEdgeLength(node);
            *start_index = node->suffixIndex;
        }        
        return;
    }

    

    for(int i = 0; i < MAX_CHAR; ++i)
    {
        if(node->children[i]== NULL) continue;
                
            int child_start_index =0;
            find_deepest_node(node->children[i], label_height + GetEdgeLength(node->children[i]), pmax_height, start_index);                    
    }     
}

void find_longest_repeated_str(char in_str[])
{
    SuffixTreeNode* node = SuffixTreeConstruct(in_str);    
    int depth = 0;
    int start_index = 0;
    find_deepest_node(node, 0, &depth, & start_index);
  
        int sz = depth;
        char* output = (char*)malloc(sizeof(char) * ( sz + 1));
        strncpy(output,in_str + start_index, sz);
        output[sz] = '\0';
        printf("longest str start [%d] end [%d], str: %s\n", start_index, start_index + sz, output);
        free(output);
    
    SuffixTreeFree();
}

int main(int argc, char* argv[])
{

    char str[] = "cabbaabb#$";
    find_longest_repeated_str(str);
    

}
