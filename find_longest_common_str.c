#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include"suffixTree.h"

// -2 for X node, -3 for Y node, -4 for XY node
int setNodeTypeDFS(SuffixTreeNode* node, char in_str[])
{
    if(node == NULL) return 0;
    if(node->suffixIndex > -1)
    {
        int k = node->start;
        for(; k < *(node->pend); ++k)
        {
            if(in_str[k] == '#') return -2;
        }
        if(in_str[*(node->pend)] == '$') return -3;
        return node->suffixIndex;
    }
    int flag = 0;
    for(int i = 0; i < MAX_CHAR; ++i)
    {
        if(node->children[i] == NULL) continue;
        int ret = setNodeTypeDFS(node->children[i], in_str);
        if(flag == 0)
        {
            flag = ret;
        }
        else if((flag == -2 && ret == -3) || (flag == -3 && ret == -2) || ret == -4)
        {
            flag = -4;            
        }                        
    }
    node->suffixIndex = flag;
    return node->suffixIndex;
}
void findDeepestNode( SuffixTreeNode* node,char in_str[], int label_height, int* pmax_height, int * pstart_index)
{
    if(node== NULL) return;

    if(node->suffixIndex != -4)
    {
        if(label_height - GetEdgeLength(node) > *pmax_height)
        {
            *pmax_height = label_height - GetEdgeLength(node);
            SuffixTreeNode* leafNode  = node;
            while(leafNode->suffixIndex <= -1);
            {
                for(int i = 0; i < MAX_CHAR; ++i)
                {
                    if(node->children[i] != NULL)
                    {
                        leafNode = node->children[i];
                        break;
                    }  
                }
            }
            *pstart_index = leafNode->suffixIndex;
            return ;
        }
    }
    else
    {
        for(int i = 0; i < MAX_CHAR; ++i)
        {
            if(node->children[i] == NULL) continue;
            findDeepestNode(node->children[i], in_str,label_height + GetEdgeLength(node->children[i]),pmax_height, pstart_index);
        }
    }

}
void printMe(int start, int end, char in_str[])
{
    for(int i = start; i <= end; ++i)
    {
        printf("%c", in_str[i]);
    }
}
void printSuffixTree(SuffixTreeNode* node, char in_str[])
{
   if(node == NULL) return;

	if(node->start != -1)
	{
		printMe(node->start,  *(node->pend), in_str);
	}
	int leaf =1;
	for(int i = 0; i< MAX_CHAR; ++i)
	{
		if(node->children[i] != NULL)
		{
			if(leaf == 1 && node->start != -1)
			{
				printf(" [%d]\n", node->suffixIndex);
			}

			leaf = 0;
			printSuffixTree(node->children[i],in_str);			
		}
	}
	if(leaf == 1)
	{		
		printf(" [%d]\n", node->suffixIndex);
	}
}

void findLongestCommonStr(char in_str1[], char in_str2[])
{
    char* in_str = (char*)malloc(strlen(in_str1) + strlen(in_str2) + 1);
    strncpy(in_str, in_str1, strlen(in_str1));
    strncat(in_str, in_str2, strlen(in_str2));
    printf("joint string : %s\n", in_str);

    SuffixTreeNode* node = SuffixTreeConstruct(in_str);
    setNodeTypeDFS(node, in_str);
    printf("=== print me ==\n");
    printSuffixTree(node, in_str);
    int depth = 0;
    
    int start_index = 0;
    findDeepestNode(node,in_str,0, &depth,&start_index);
    
    int sz = depth;
    char* output = (char*)malloc(sizeof(char)* (sz + 1));
    strncpy(output, in_str + start_index, sz);
    output[sz] = '\0';
    printf("deepest node from [%d] to [%d], str: %s", start_index, start_index + sz, output);
    free(output);
    
}

int main(int argc, char* argv[])
{
    char in_str1[] = "xabxa#";
    char in_str2[] = "babxba$";
    findLongestCommonStr(in_str1, in_str2);
}