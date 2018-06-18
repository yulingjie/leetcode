#ifndef __SUFFIX_TREE_H__
#define __SUFFIX_TREE_H__

#define MAX_CHAR 256
typedef struct suffix_tree_node SuffixTreeNode;
struct suffix_tree_node
{
	struct suffix_tree_node *children[MAX_CHAR];
	struct suffix_tree_node *suffixLink;
	int start;
	int *pend;
	int suffixIndex;
};

int GetEdgeLength(SuffixTreeNode* node);
SuffixTreeNode* SuffixTreeConstruct(char in_str[]);
void SuffixTreeFree();

int SuffixTreeDoTraversal(SuffixTreeNode* node, char* str, int idx, char in_str[], SuffixTreeNode** pointer_return_node);
#endif