#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "suffixTree.h"
#define MAX_CHAR 256

struct suffix_tree_node
{
	struct suffix_tree_node *children[MAX_CHAR];
	struct suffix_tree_node *suffixLink;
	int start;
	int *pend;
	int suffixIndex;
};
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
SuffixTreeNode *CreateNode(int startm, int *pend);
void ExtendSuffixTree(SuffixEnv *penv, int phase);
int WalkDown(SuffixEnv *penv);

SuffixTreeNode *SuffixTreeConstruct(char in_str[])
{
	SuffixEnv * penv= (SuffixEnv*)malloc(sizeof(int));
	int *pend = (int*)malloc(sizeof(int));
	*pend = -1;
	penv->pend = pend;
	


}
int WalkDown(SuffixEnv *penv)
{
	SuffixTreeNode *next_node = penv->pactive_node->children[(int)penv->in_s[penv->active_edge_index]];
	int length = *(next_node->pend) - next_node->start;
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
	++penv->pend; // end move to next character
	SuffixTreeNode* lastNewNode = NULL;
	while (penv->remaining_suffix_count > 0)
	{
		char current_char = penv->in_s[phase];
		char current_edge = penv->in_s[penv->pactive_node->start];
		if (penv->active_length == 0) // APCFZ rule 1
		{
			current_edge = current_char;
		}
		if (penv->pactive_node->children[(int)current_edge] == NULL)
		{
			// apply rule 2: create new node
			SuffixTreeNode *new_node = CreateNode(phase, penv->pend);
			new_node->suffixLink = penv->proot;
			penv->pactive_node->children[(int)current_edge] = new_node;
		}
		else
		{
			if (WalkDown(penv))
				continue;
			
			// apply rule 3: break loop
			if (penv->in_s[penv->pactive_node->start + penv->active_length] == current_char) 
			{
				break;
			}
			// apply rule2: create new node
			int * psplit_node_end =(int*)malloc(sizeof(int));
			*psplit_node_end =penv->pactive_node->start + penv->active_length -1 ;
			SuffixTreeNode* split_node = CreateNode(penv->pactive_node->start, psplit_node_end);
			SuffixTreeNode* next_node = penv->pactive_node->children[(int)(penv->in_s[penv->active_edge_index])];
			penv->pactive_node->children[(int)(penv->in_s[penv->active_edge_index])] = split_node;
			split_node->children[(int)(penv->in_s[penv->pactive_node->start + penv->active_length])] = next_node;

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

/*
SuffixTreeNode* create_node(int start, int * end)
{
	
}
int edge_length(SuffixTreeNode* node)
{
	return *(node->end) - node->start + 1;
}
void print(int i, int j, char* S)
{
	int k;
	for(k = i; k <=j; ++k)
	{
		printf("%c", S[k]);
	}
}
void set_suffix_index_by_dfs(SuffixTreeNode* node, int labelHeight,char *S,int size)
{
	if(node == NULL) return;
	
	if(node->start != -1)
	{
		print(node->start, *(node->end), S);
	}
	int leaf = 1;
	int i ;
	for(i = 0; i < MAX_CHAR; ++i)
	{
		if(node->children[i] != NULL)
		{
			if(leaf == 1&& node->start != -1)
			{
				printf(" [%d]\n", node->suffixIndex);
			} 
			
			leaf = 0;
			set_suffix_index_by_dfs(node->children[i], 
			labelHeight + edge_length(node->children[i]),S, size);
		}
	}
	if( leaf == 1)
	{
		node->suffixIndex = size - labelHeight;
		printf(" [%d]\n", node->suffixIndex);
	}
}
void free_suffix_tree_by_post_order(SuffixTreeNode* node)
{
	if(node == NULL) return;
	int i ;
	for(i = 0; i < MAX_CHAR; ++i)
	{
		if(node->children[i] != NULL)
		{
			free_suffix_tree_by_post_order(node->children[i]);
		}
	}
	if(node->suffixIndex == -1)
	{
		free(node->end);
	}
	free(node);
}
int walk_down(ActivePoint* ap,SuffixTreeNode* node, char * S)
{
	if(ap->activeLength >= edge_length(node))
	{
		ap->activeNode = node;
		ap->activeLength -= edge_length(node);
		ap->activeTree = S[*(node->end) + 1];
		return 1;
	}
	return 0;
}

void construct_suffix_tree(char* s, int size)
{
	
	char* S = s;
	int* endPos = (int*)malloc(sizeof(int));
	*endPos = 0;
	
	int * rootEnd = (int*)malloc(sizeof(int));
	*rootEnd = -1;
	
	SuffixTreeNode* root = create_node(-1, rootEnd);
	
	ActivePoint* ap= (ActivePoint*) malloc(sizeof(ActivePoint));
	ap->activeNode = root;
	ap->activeLength = 0;
	ap->activeTree = '\0';
	int phase = 0;
	int remainingSuffixCount = 0;
	
	SuffixTreeNode* lastNewNode = NULL;
	
	while(S[phase] != '\0')
	{
		*endPos = phase;
		++ remainingSuffixCount;
		while(remainingSuffixCount > 0)
		{
			if(ap->activeLength == 0) ap->activeTree = S[phase];
			
			if(ap->activeNode->children[ap->activeTree] == NULL)
			{
				ap->activeNode->children[ap->activeTree] = create_node(phase,endPos);
				
				if(lastNewNode != NULL)
				{
					lastNewNode ->suffixLink = ap->activeNode;
					lastNewNode = NULL;
				}
			}
			else
			{
				SuffixTreeNode* next = ap->activeNode->children[ap->activeTree];
				if(walk_down(ap, next, S)) continue;
				
				if(S[next->start + ap->activeLength] == S[phase])
				{
					if(lastNewNode != NULL && ap->activeNode != root)
					{
						lastNewNode -> suffixLink = ap->activeNode;
						lastNewNode = NULL;
					}
					++ap->activeLength;
					break;
				}
				
				int* splitEnd = (int*)malloc(sizeof(int));
				*splitEnd = next->start + ap->activeLength - 1;
				SuffixTreeNode* splitNode = create_node(next->start, splitEnd);
				ap->activeNode->children[ap->activeTree] = splitNode;
				
				splitNode->children[S[phase]] = create_node(phase, endPos);
				next->start += ap->activeLength;
				splitNode->children[S[next->start]] = next;
				
				if(lastNewNode != NULL)
				{
					lastNewNode->suffixLink = splitNode;
				}
				
				lastNewNode = splitNode;
			}
			-- remainingSuffixCount;
			if(ap->activeNode == root && ap->activeLength > 0)
			{
				-- ap->activeLength;
				ap->activeTree = S[phase - remainingSuffixCount + 1];
			}else if(ap->activeNode != root)
			{
				ap->activeNode = ap->activeNode->suffixLink;
			}
		}
		++ phase;
	}
	int labelHeight = 0;
	set_suffix_index_by_dfs(root, labelHeight,s, size);
	
	free_suffix_tree_by_post_order(root);

	
}
int main(int argc, char* argv[])
{
	char text[] = "abcabxabcd$";
	construct_suffix_tree(text, (int)strlen(text));
}

*/
