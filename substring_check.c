#include <stdio.h>
#include <stdlib.h>
#include "suffixTree.h"
int traverseEdge(char* str, int idx, int start, int end, char in_str[])
{
    int k = 0;
    for(k = start; k <= end && str[idx] != '\0'; ++k, ++idx)
    {
        if(in_str[k] != str[idx])
        {
            return -1;
        }
    }
    if(str[idx] == '\0')
    {
        return 1;
    }
    return 0;
}
int doTraversal(SuffixTreeNode* node, char* str, int idx, char in_str[])
{
    if(node == NULL)
    {
        return -1;
    }
    int res = -1;
    if(node->start != -1)
    {
        res = traverseEdge(str, idx, node->start, *(node->pend), in_str);
        if(res != 0)
        {
            return res;
        }
    }
    idx += GetEdgeLength(node);
    if(node->children[str[idx]] != NULL)
    {
        return doTraversal(node->children[str[idx]],str,idx,in_str);
    }
    return -1;
}
void checkForSubString(char* str, char in_str[], SuffixTreeNode* root)
{
    int res = doTraversal(root, str, 0, in_str);
    if(res == 1)
    {
        printf("Pattern <%s> is a Substring \n", str);
    }
    else
    {
        printf("Pattern <%s> is NOT a Substring\n", str);
    }
}
int main(int argc, char* argv)
{
    char in_str[] = "THIS IS A TEST TEXT$";
    SuffixTreeNode* node =SuffixTreeConstruct(in_str);

    checkForSubString("TEST",in_str, node);
    checkForSubString("A", in_str, node);
    checkForSubString(" ", in_str, node);
    checkForSubString("IS A", in_str, node);
    checkForSubString(" IS A ", in_str, node);
    checkForSubString("TEST1", in_str, node);
    SuffixTreeFree();
}