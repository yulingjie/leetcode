#include <stdio.h>
#include <stdlib.h>
#include "suffixTree.h"

void find_deepest_node(SuffixTreeNode* node, SuffixTreeNode** pointer_node,int* depth, int * start_index)
{
    if(node == NULL) return;
    if(node->suffixIndex != -1) 
    {
        *start_index = node->suffixIndex;
        return;
    }

    SuffixTreeNode* child_node = NULL;

    for(int i = 0; i < MAX_CHAR; ++i)
    {
        if(node->children[i]== NULL) continue;
        if(node->children[i]->suffixIndex == -1)
        {
            int childDepth = *depth + 1;
        
            find_deepest_node(node->children[i], &child_node, &childDepth, start_index);
            if(child_node != NULL && childDepth > *depth)
            {
                *depth = childDepth;
                *pointer_node = child_node;                
            }
        }
    }    
    if(child_node == NULL)
    {
        *pointer_node = node;        
    }
}

void find_longest_repeated_str(char in_str[])
{
    SuffixTreeNode* node = SuffixTreeConstruct(in_str);
    SuffixTreeNode* deepest_node = NULL;
    int depth = 0;
    int start_index = 0;
    find_deepest_node(node, & deepest_node, & depth, & start_index);
    if(deepest_node != NULL)
    {
        
        printf("longest str start [%d] end [%d]\n", start_index, *deepest_node->pend);
    }
    SuffixTreeFree();
}

int main(int argc, char* argv[])
{
    char str1[] = "ABABABA$";
    find_longest_repeated_str(str1);


}
