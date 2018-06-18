#include <stdio.h>
#include<stdlib.h>
#include "suffixTree.h"

void DFSTraverseAllLeaf(SuffixTreeNode* node)
{
    if(node == NULL) return;
    for(int i = 0; i < MAX_CHAR; ++i)
    {
        if(node->children[i] != NULL && node->children[i]->suffixIndex != -1)
        {
            printf("at indices %d \n", node->children[i]->suffixIndex);
        }
        else
        {
            if(node->children[i] != NULL && node->children[i]->suffixIndex == -1)
            {
                DFSTraverseAllLeaf(node->children[i]);
            }
        }
    }
    if(node->suffixIndex != -1)
    {
        printf("at indices %d \n", node->suffixIndex);
    }
}

void SearchingAllPatterns(char* str_pattern, SuffixTreeNode* node, char* in_str)
{
    SuffixTreeNode* pointer_node ;
    if(SuffixTreeDoTraversal(node, str_pattern, 0,in_str, &pointer_node) == 1)
    {
        DFSTraverseAllLeaf(pointer_node);
    }
}
int main(int argc, char* argv)
{
    char in_str[] = "abcabxabcd$";
    SuffixTreeNode* node = SuffixTreeConstruct(in_str);
    SearchingAllPatterns("ab", node, in_str);
    SuffixTreeFree();
}