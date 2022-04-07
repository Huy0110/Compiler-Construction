#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#define CONSTANT 100

typedef int elementtype; 

struct list_el{
    elementtype element;
    struct list_el *next;
    struct list_el *prev;
};
typedef struct list_el dblist;

typedef struct elm{
	char word[50];
	int appearCount;
	dblist *rootLine, *curLine, *tailLine;
}elmType;

typedef struct node_type{
    elmType element;
    struct node_type *left,*right;
}nodeType;

typedef nodeType *treetype;

void makeNullList(dblist **root,dblist **cur,dblist **tail);

dblist* makeNewNode(elementtype data);

void displayNode(dblist* p);

void traverseList(dblist *root);

void appendList(elementtype data,dblist **root,dblist **cur,dblist **tail);

void freeNode(dblist **root);

void makeNullTree(treetype* N);

nodeType* Create_Node(elmType data);

int isEmptyTree(treetype N);

int isLeaf(treetype N);

int compare(elmType a, elmType b);

void insertNode(treetype* T,elmType data);

void inOrderPrint(treetype T);

treetype searchT(treetype T, elmType x);

void freeTree(treetype T);
