#include<stdio.h>
#include<stdlib.h>
#include "suffixTree.h"


int main(int argc, char const *argv[])
{
    SuffixTreeNode* node = SuffixTreeConstruct("abcabxabcd$");
    SuffixTreeFree();
    return 0;
}
