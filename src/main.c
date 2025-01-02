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
int booksInLibrary;

// Book struct
typedef struct book{
	char title[STRSIZE];
	char author[STRSIZE];
	char isbn[13];
	int isAvailable;
} book;

// Binary Search Tree struct
typedef struct treenode{
	char title[256];
	char isbn[256];
	int index;
	struct treenode* left;
	struct treenode* right;
} treenode;


// Function declaration
int insertBook(book* books, treenode* booktree, const char* title, const char* author, const char* isbn);
int insertToArray(book** books, const char* title, const char* author, const char* isbn);
int insertToBST(treenode** bookTreeRoot, const char* title, const char* isbn);
treenode* createNode(const char* title, const char* isbn);


int main(int argc, char* argv[])
{
	booksInLibrary = 0;
	// Use array to store the book structs
	book* books = malloc(MAXBOOKS*sizeof(book));
	if(books == NULL)
	{
		printf("Failed to heap allocate memory for book array.\n");
		return EXIT_FAILURE;
	}

	// Use Binary search tree to store indicies to the array
	treenode* booktree = NULL;	// Let insertToBST be responsible for initializing it

	if(booksInLibrary < MAXBOOKS)
	{
		// Just a placeholder
		if(insertBook(books, booktree,"","", ""))
		{
			booksInLibrary++;
		}
		else
		{
			printf("Failed to insert book.\n");
		}
	}

	return 0;
}

treenode* createNode(const char* title, const char* isbn)
{
	treenode* node = malloc(sizeof(treenode));

	if(strcpy_s(node->title, STRSIZE, title) || strcpy_s(node->isbn, STRSIZE, isbn))
	{
		// If setting the title and isbn throws an error
		return NULL;
	}
	
	node->index = booksInLibrary;
	node->left = NULL;
	node->right = NULL;

	return node;
}

int insertBook(book* books, treenode* booktree, const char* title, const char* author,
	const char* isbn)
{
	// Find a spot in the Registry (tree) first before inserting to shelf (Array)
	if(insertToBST(&booktree, title, isbn))
	{
		return insertToArray(&books, title, author, isbn);		
	}
	else
	{
		return 0;
	}
}

int insertToBST(treenode** bookTreeRoot, const char* title, const char* isbn)
{
	treenode* root = *bookTreeRoot;

	// If the tree is empty
	if(root == NULL)
	{
		*bookTreeRoot = createNode(title, isbn);
		if(bookTreeRoot == NULL)
		{
			return 0;
		}
		else
		{
		return 1;	
		}
	}

	// If there is a book with the same ISBN, return 0
	if(strcmp(root->isbn, isbn) == 0)
		return 0;

	if(strcmp(root->isbn, isbn) > 0)
	{
		return insertToBST(&root->left, title, isbn);
	}
	else
	{
		return insertToBST(&root->right, title, isbn);
	}
}

int insertToArray(book** books, const char* title, const char* author,
	const char* isbn)
{
	strcpy_s(books[booksInLibrary]->title, STRSIZE, title);
	strcpy_s(books[booksInLibrary]->author, STRSIZE, author);
	strcpy_s(books[booksInLibrary]->isbn, STRSIZE, isbn);
	books[booksInLibrary]->isAvailable = 1;

	return 1;
}