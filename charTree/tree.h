#ifndef __LQ_TRIETREE_H
#define __LQ_TRIETREE_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define ALPHABET_NUMBER 26  // alphabet

typedef struct TrieNode{
	int 	  isLeaf;
	struct TrieNode* child[ALPHABET_NUMBER];
	char 	  value;
	int       num;
}TrieNode;

void initTreeNode(TrieNode* pNode);
void createTree(TrieNode** root);
void insertTree(TrieNode* root , char* str);
int search(TrieNode* root , char* str);




#endif /* __LQ_TRIETREE_H */
