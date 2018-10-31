#include "tree.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <mysql.h>

#define NUMBER_WORDS    100
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
			//printf("new value : %c\n",temp_Node->child[index]->value);
		}else{
			//printf("exist value : %c\n",temp_Node->child[index]->value);
			temp_Node->child[index]->num = temp_Node->child[index]->num + 1;
		}

		temp_Node = temp_Node->child[index];		
	}
	
	temp_Node->isLeaf = 1;

	//printf("finish insert\n");
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

static inline void _mysql_check(MYSQL * con) {
    fprintf(stderr, "%s\n", mysql_error(con));
    mysql_close(con);
    exit(EXIT_FAILURE);
}

void main(){

	TrieNode* root = NULL;
	createTree(&root);

	MYSQL *con = mysql_init(NULL);
	if (con == NULL) {
		fprintf(stderr, "%s\n", mysql_error(con));
		exit(EXIT_FAILURE);
	}

	if (!mysql_real_connect(con, "127.0.0.1", "root", "newpassword", "words", 0, NULL, 0)) {
		_mysql_check(con);
	}  


	puts("mariadb is connect and run succesed!");



	printf("use words\n");

	char* str = "select* from words;";
	if (mysql_real_query(con, str,strlen(str))){
		printf("wrong \n");
		_mysql_check(con);
	}
	printf("%s\n",str);
// ----------------------------------------------------------- 

    MYSQL_RES * res = mysql_store_result(con);
    if (NULL == res)
	{
		printf("error!\n");
        _mysql_check(con);
	}

    MYSQL_ROW row;
    unsigned rlen = mysql_num_fields(res);
    printf("mariadb now row length = %u\n", rlen);
    
 	int counter = 0;
    while ((row = mysql_fetch_row(res))) {
        char* temp = row[1];
		int i = 0;
		int isword = 1;
		for(i = 0; i < strlen(temp); i++){
			if(temp[i] > 'z' || temp[i] < 'a'){
				isword = 0;
				break;
			}
				
		}
		if(isword == 1){
			if(strcmp(row[1],"childe") == 0)
			{
				printf("%s--------------\n" , row[1]);
				getchar();
			}
			insertTree(root,row[1]);
            printf("%s ", row[1]);
        	putchar('\n');
			counter = counter + 1;
		}
		//if(counter == NUMBER_WORDS)
		//	break;
    }
	
	mysql_free_result(res);
	mysql_close(con); 

	printf(" %d words in database\n",counter);
    
// ----------------------------------------------------------- 

	// ------ make up tree of word , store the word
	//char* train_string = "liqing";
	//char* string_1 = "lijunjie";
	//char* string_2 = "linjunjie";

	//char* search_1 = "lijunjie";
	//char* search_2 = "linyoujia";

	//TrieNode* root = NULL;
	//createTree(&root);
	
	//insertTree(root,train_string);
	//insertTree(root,string_1);
	//insertTree(root,string_2);


	// ------ search word
	char search_string[100];
	printf("input search string : ");
	scanf("%s",search_string); 
	while(1){
		if( search(root,search_string) == 1 )
			printf("%s is in the set\n",search_string);
		else
			printf("%s is ----- not in set\n",search_string);
		printf("input search string : ");
		scanf("%s",search_string);
	}

}
















