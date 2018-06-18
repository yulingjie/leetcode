#include <stdio.h>
#include <stdlib.h>
#include "suffixTree.h"

void checkForSubString(char* str, char in_str[], SuffixTreeNode* root)
{
    int res = SuffixTreeDoTraversal(root, str, 0, in_str, NULL);
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