#include "tree.h"
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

void initTreeNode(TrieNode* pNode){
	pNode->isLeaf = 0;
	int i = 0;
	for(i = 0; i < ALPHABET_NUMBER; i++)
		pNode->child[i] = NULL;
	pNode->value = '0';
	pNode->num = 0;
}


void createTree(TrieNode** root){
	printf("createTree()\n");
	*root = (TrieNode*)malloc(sizeof(TrieNode));
	initTreeNode(*root);
}

void insertTree(TrieNode* root , char* str){
	if(root == NULL)
		return;
	if(str == NULL || strlen(str) == 0)
		return;

	TrieNode* temp_Node = root;

	int i = 0;
	for(i = 0; i < strlen(str); i++){
		int index = str[i] - 'a';
		if(temp_Node->child[index] == NULL){
			temp_Node->child[index] = (TrieNode*)malloc(sizeof(TrieNode));
			initTreeNode(temp_Node->child[index]);
			temp_Node->child[index]->value = str[i];
			temp_Node->child[index]->num++;
			printf("new value : %c\n",temp_Node->child[index]->value);
		}else{
			printf("exist value : %c\n",temp_Node->child[index]->value);
			temp_Node->child[index]->num = temp_Node->child[index]->num + 1;
		}

		temp_Node = temp_Node->child[index];		
	}
	
	temp_Node->isLeaf = 1;

	printf("finish insert\n");
}

int search(TrieNode* root , char* str){
	if(root == NULL)
		return -1;
	if(str == NULL || strlen(str) == 0)
		return -1;

	TrieNode* temp_Node = root;

	int i = 0;
	for(i = 0; i < strlen(str); i++){
		int index = str[i] - 'a';
		if(temp_Node->child[index] != NULL){
			temp_Node = temp_Node->child[index];
		}else{
			return -1;	
		}		
	}
	
	return temp_Node->isLeaf;

}

void main(){

	// ------ make up tree of word , store the word
	char* train_string = "liqing";
	char* string_1 = "lijunjie";
	char* string_2 = "linjunjie";

	char* search_1 = "lijunjie";
	char* search_2 = "linyoujia";

	TrieNode* root = NULL;
	createTree(&root);
	
	insertTree(root,train_string);
	insertTree(root,string_1);
	insertTree(root,string_2);


	// ------ search word
	if( search(root,search_1) == 1 )
		printf("%s is in the set\n",search_1);
	else
		printf("%s is not in set\n",search_1);

	 if( search(root,search_2) == 1 )
		printf("%s is in the set\n",search_2);
	else
		printf("%s is not in set\n",search_2);


}














