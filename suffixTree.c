#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "suffixTree.h"



typedef struct suffix_env
{
	SuffixTreeNode *proot;
	SuffixTreeNode *pactive_node;
	int active_length;
	int active_edge_index;
	char *in_s;
	int *pend;
	int remaining_suffix_count;
} SuffixEnv;
typedef struct suffix_active_point
{
	SuffixTreeNode *activeNode;
	int activeLength;
	char activeTree;
} ActivePoint;

SuffixEnv * pointer_env;
SuffixTreeNode *CreateNode(int startm, int *pend);
void ExtendSuffixTree(SuffixEnv *penv, int phase);
int WalkDown(SuffixEnv *penv);
int SuffixTreeTraverseEdge(char* str,int idx, int start, int end, char in_str[]);
void SetSuffixIndexByDFS(SuffixTreeNode* penv, int label_height, char in_s[]);
void FreeSuffixTree(SuffixTreeNode* penv);
int GetEdgeLength(SuffixTreeNode* node)
{
	if(node->start == -1)return 0;
	return *node->pend - node->start + 1;
}
SuffixTreeNode *SuffixTreeConstruct(char in_str[])
{
	SuffixEnv *penv= (SuffixEnv*)malloc(sizeof(SuffixEnv));	
	penv->pend = (int*)malloc(sizeof(int));
	*(penv->pend) = -1;	
	int * rootEnd = (int*)malloc(sizeof(int));
	*rootEnd = -1;
	SuffixTreeNode* proot = CreateNode(-1, rootEnd);
	penv->proot = proot;
	penv->pactive_node = proot;
	penv->active_length = 0;
	penv->active_edge_index = -1;
	penv->in_s = in_str;
	penv->remaining_suffix_count = 0;
	pointer_env = penv;
	for(int i = 0; i < strlen(in_str); ++i)
	{
		ExtendSuffixTree(penv, i);
	}

	SetSuffixIndexByDFS(penv->proot, 0, penv->in_s);

	return penv->proot;
	
}
void SuffixTreeFree()
{
	FreeSuffixTree(pointer_env->proot);
	free(pointer_env->pend);
	free(pointer_env);
}
void FreeSuffixTree(SuffixTreeNode *pnode)
{
	if(pnode == NULL) return;

	int i = 0;
	for(i = 0; i < MAX_CHAR; ++i)
	{
		if(pnode->children[i] != NULL)
		{
			FreeSuffixTree(pnode->children[i]);
		}
	}
	if(pnode->suffixIndex == -1)
	{
		free(pnode->pend);
	}
	free(pnode);
	
}
void print(int i, int j, char in_s[])
{
	int k;
	for(k =i; k <=j; ++k)
	{
		printf("%c", in_s[k]);
	}
}

void SetSuffixIndexByDFS(SuffixTreeNode* node, int label_height, char in_s[])
{
	if(node == NULL) return;

	if(node->start != -1)
	{
		print(node->start,  *(node->pend), in_s);
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
			SetSuffixIndexByDFS(node->children[i],label_height + GetEdgeLength(node->children[i]), in_s);			
		}
	}
	if(leaf == 1)
	{
		node->suffixIndex = strlen(in_s) - label_height;
		printf(" [%d]\n", node->suffixIndex);
	}
	
}
int WalkDown(SuffixEnv *penv)
{
	SuffixTreeNode *next_node = penv->pactive_node->children[(int)penv->in_s[penv->active_edge_index]];
	int length = GetEdgeLength(next_node);
	if (penv->active_length >= length)
	{
		penv->pactive_node = next_node;
		penv->active_length -= length;
		penv->active_edge_index += length;
		return 1;
	}
	return 0;
}
void ExtendSuffixTree(SuffixEnv *penv, int phase)
{
	if (penv == NULL)
		return;
	if (penv->in_s == NULL)
		return;
	++penv->remaining_suffix_count;
	*penv->pend = *(penv->pend) + 1 ;// end move to next character
	SuffixTreeNode* lastNewNode = NULL;
	while (penv->remaining_suffix_count > 0)
	{
		char current_char = penv->in_s[phase];
		if (penv->active_length == 0) // APCFZ rule 1
		{
			//current_edge = current_char;
			penv->active_edge_index = phase;
		}
		char current_edge = penv->in_s[penv->active_edge_index];
		if (penv->pactive_node->children[(int)current_edge] == NULL)
		{
			// apply rule 2: create new node
			SuffixTreeNode *new_node = CreateNode(phase, penv->pend);
			new_node->suffixLink = penv->proot;
			penv->pactive_node->children[(int)current_edge] = new_node;

			if(lastNewNode != NULL)
			{
				lastNewNode->suffixLink = penv->pactive_node;
				lastNewNode = NULL;
			}
		}
		else
		{
			if (WalkDown(penv))
				continue;
			
			SuffixTreeNode *next_node = penv->pactive_node->children[(int)penv->in_s[penv->active_edge_index]];
			// apply rule 3: break loop
			if (penv->in_s[next_node->start + penv->active_length] == current_char) 
			{
				if(lastNewNode != NULL && penv->pactive_node != penv->proot)
				{
					lastNewNode->suffixLink = penv->pactive_node;
					lastNewNode = NULL;
				}
				++ penv->active_length;
				break;
			}
			// apply rule2: create new node
			 
			int * psplit_node_end =(int*)malloc(sizeof(int));
			*psplit_node_end =next_node->start + penv->active_length -1 ;		
			
			SuffixTreeNode* split_node = CreateNode(next_node->start, psplit_node_end);
			penv->pactive_node->children[(int)(penv->in_s[penv->active_edge_index])] = split_node;

			next_node->start += penv->active_length;
			split_node->children[(int)(penv->in_s[next_node->start])] = next_node;

			SuffixTreeNode* new_node = CreateNode(phase, penv->pend);
			split_node->children[(int)(penv->in_s[phase])] = new_node;

			split_node->suffixLink = penv->proot;

			if(lastNewNode != NULL)
			{
				lastNewNode->suffixLink = split_node;
				lastNewNode = NULL;
			}
			lastNewNode = split_node;
		}
		-- penv->remaining_suffix_count;

		if(penv->pactive_node == penv->proot && penv->active_length > 0)
		{
			penv->active_length --;
			penv->active_edge_index = phase - penv->remaining_suffix_count + 1;
		}
		else if(penv->pactive_node != penv->proot)
		{
			penv->pactive_node = penv->pactive_node->suffixLink;
		}
	}
}
SuffixTreeNode *CreateNode(int start, int *pointer_end)
{
	SuffixTreeNode *node = (SuffixTreeNode *)malloc(sizeof(SuffixTreeNode));
	node->start = start;
	node->pend = pointer_end;
	node->suffixIndex = -1;
	node->suffixLink = NULL;
	for (int i = 0; i < MAX_CHAR; ++i)
	{
		node->children[i] = NULL;
	}
	return node;
}
int SuffixTreeTraverseEdge(char* str,int idx, int start, int end, char in_str[])
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

int SuffixTreeDoTraversal(SuffixTreeNode* node, char* str, int idx, char in_str[], SuffixTreeNode** pointer_return_node)
{
	 if(node == NULL)
    {
        return -1;
    }
    int res = -1;
    if(node->start != -1)
    {
        res = SuffixTreeTraverseEdge(str, idx, node->start, *(node->pend), in_str);
        if(res != 0)
        {
			if(pointer_return_node != NULL)
			{
				*pointer_return_node = node;
			}
			
            return res;
        }
    }
    idx += GetEdgeLength(node);
    if(node->children[str[idx]] != NULL)
    {
        return SuffixTreeDoTraversal(node->children[str[idx]],str,idx,in_str, pointer_return_node);
    }
    return -1;
}

