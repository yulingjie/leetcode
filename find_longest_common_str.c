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
// X 1, Y 2, XY 3
int doTraversal(SuffixTreeNode* node,char in_str[], int label_height, int * pmax_height, int * pstart_index, int *pcur_start_index)
{
    if(node == NULL) return 0;
    if(node->suffixIndex == -1) // internal node
    {
        int flag = 0;
        int xy_start_index = -1;

        for(int i = 0; i < MAX_CHAR; ++i)
        {
            if(node->children[i] == NULL) continue;
            
            int child_label_height = GetEdgeLength(node->children[i]) + label_height;
            
            int rt =  doTraversal(node->children[i],in_str, child_label_height, pmax_height, pstart_index, pcur_start_index);        
            xy_start_index = *pcur_start_index;
            flag |= rt;           
        }
        if(flag == 3 && label_height > (*pmax_height))
        {
            *pmax_height = label_height;
            *pstart_index = xy_start_index;
        }

        return flag;
    }
    else 
    {
        *pcur_start_index = node->suffixIndex;
        for(int j = node->start; j < *(node->pend); ++j)
        {
            if(in_str[j] == '#') return 1;            
        }        
        if(in_str[*(node->pend)] == '$') return 2;
        return node->suffixIndex;
    }

}
void findLongestCommonStr(char in_str1[], char in_str2[])
{
    char* in_str = (char*)malloc(strlen(in_str1) + strlen(in_str2) + 1);
    strncpy(in_str, in_str1, strlen(in_str1));
    strncat(in_str, in_str2, strlen(in_str2));
    printf("joint string : %s\n", in_str);

    SuffixTreeNode* node = SuffixTreeConstruct(in_str);
   // setNodeTypeDFS(node, in_str);
   // printf("=== print me ==\n");
   // printSuffixTree(node, in_str);
   // int depth = 0;    
   // int start_index = 0;
   // findDeepestNode(node,in_str,0, &depth,&start_index);
   int depth = 0;
   int start_index = 0;
   int cur_start_index = -1;
    doTraversal(node, in_str,0, &depth, &start_index, &cur_start_index); 
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