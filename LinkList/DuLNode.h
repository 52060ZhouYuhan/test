#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct DuLNode{
	struct DuLNode *prior;
	struct DuLNode *next;
	int data;
}*DuLinkList;
