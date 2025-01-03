/*
*
* Library-Management-System
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXBOOKS	1000000
#define STRSIZE		256

// Book struct
typedef struct book{
	char title[STRSIZE];
	char author[STRSIZE];
	char isbn[13];
	int isAvailable;
} book;

// Binary Search Tree struct
typedef struct treenode{
	char title[STRSIZE];
	char isbn[STRSIZE];
	int index;
	struct treenode* left;
	struct treenode* right;
} treenode;

// Struct to keep track of empty slots in the books array after deletion
typedef struct slots{
	unsigned int count;
	int slots[MAXBOOKS];
} slots;

// Globals
extern int booksInLibrary;
extern int slotsUsed;
extern slots freeSlots;


// Function declaration
treenode* createNode(book* book);
treenode* getSuccessor(treenode* node);
int insertBook(book* booksArray, treenode** booktree, book* book);
int insertToArray(book* booksArray, book* book);
int insertToBST(treenode** bookTreeRoot, book* book);

int searchBook(treenode* booksTree, book* bookArray, const char* identifier, int isISBN, book* out_book);
int searchBST(treenode* booksTree, const char* identifier, int isISBN);

int deleteBook(treenode** booksTree, book* bookArray, const char* identifier, int isISBN);
int deleteNode(treenode** booksTree, const char* identifier);

