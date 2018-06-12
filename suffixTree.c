#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_CHAR 256




typedef struct suffix_tree_node
{
	struct suffix_tree_node* children[MAX_CHAR];
	struct suffix_tree_node* suffixLink;
	int start;
	int* end;
	int suffixIndex;
	int isLeaf;
} SuffixTreeNode;

typedef struct suffix_active_point
{
	SuffixTreeNode* activeNode;
	int activeLength;
	char activeTree;
} ActivePoint;




SuffixTreeNode* create_node(int start, int * end)
{
	SuffixTreeNode* node = (SuffixTreeNode*)malloc(sizeof(SuffixTreeNode));
	node->start =start;
	node->end = end;
	node->suffixIndex = -1;
	node->suffixLink = NULL;
	for(int i = 0; i < MAX_CHAR; ++i)
	{
		node->children[i] = NULL;
	}
	node->isLeaf = 1;
	return node;
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