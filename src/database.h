/*
*
* Library-Management-System
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAXBOOKS	2000000
#define STRSIZE		256
#define ISBNSIZE	14		// 13 + null termination

// Book struct
typedef struct book{
	char title[STRSIZE];
	char author[STRSIZE];
	char isbn[ISBNSIZE];
	int isAvailable;
} book_t;

// Binary Search Tree struct
typedef struct treenode{
	char title[STRSIZE];
	char isbn[STRSIZE];
	int index;
	struct treenode* left;
	struct treenode* right;
} treenode_t;

// Struct to keep track of empty slots in the books array after deletion
typedef struct slots{
	unsigned int count;
	int slots[MAXBOOKS];
} slots_t;

// Globals
extern int booksInLibrary;
extern int slotsUsed;
extern slots_t freeSlots;


// Function declaration
treenode_t* createNode(book_t* book);
treenode_t* getSuccessor(treenode_t* node);
int insertBook(treenode_t** booktree, book_t* booksArray, book_t* book);
int insertToArray(book_t* booksArray, book_t* book);
int insertToBST(treenode_t** bookTreeRoot, book_t* book);

int searchBook(treenode_t* booksTree, book_t* bookArray, const char* identifier, int isISBN, book_t* out_book);
int searchBST(treenode_t* booksTree, const char* identifier, int isISBN);

int deleteBook(treenode_t** booksTree, book_t* bookArray, const char* identifier, int isISBN);
int deleteNode(treenode_t** booksTree, const char* identifier);

int insertBooksFromCSV(const char* file, treenode_t** booksTree, book_t* booksArray);