/*
*
* Library-Management-System
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>


#define MAXBOOKS	INT_MAX
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
	char title[STRSIZE];
	char isbn[STRSIZE];
	int index;
	struct treenode* left;
	struct treenode* right;
} treenode;


// Function declaration
treenode* createNode(book* book);
int insertBook(book* books, treenode* booktree, book* book);
int insertToArray(book* books, book* book);
int insertToBST(treenode** bookTreeRoot, book* book);

int searchBook(treenode* booksTree, book* bookArray, const char* identifier, int isISBN, book* out_book);
int searchBST(treenode* booksTree, const char* identifier, int isISBN);


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

	book book = {0};
	if(booksInLibrary < MAXBOOKS)
	{
		// Just a placeholder
		if(insertBook(books, booktree, &book))
		{
			booksInLibrary++;
		}
		else
		{
			printf("Failed to insert book.\n");
		}
	}

	struct book book1;
	
	// Another placeholder
	if(!searchBook(booktree, books, "", 1, &book1))
	{
		printf("Could not find book.\n");
	}

	return 0;
}

treenode* createNode(book* book)
{
	treenode* node = malloc(sizeof(treenode));

	if(strcpy_s(node->title, STRSIZE, book->title) || strcpy_s(node->isbn, STRSIZE, book->isbn))
	{
		// If setting the title and isbn throws an error
		return NULL;
	}
	
	node->index = booksInLibrary;
	node->left = NULL;
	node->right = NULL;

	return node;
}

int insertBook(book* books, treenode* booktree, book* book)
{
	// Find a spot in the Registry (tree) first before inserting to shelf (Array)
	if(insertToBST(&booktree, book))
	{
		return insertToArray(books, book);		
	}
	else
	{
		return 0;
	}
}

int insertToBST(treenode** bookTreeRoot, book* book)
{
	treenode* root = *bookTreeRoot;

	// If the tree is empty
	if(root == NULL)
	{
		*bookTreeRoot = createNode(book);
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
	if(strcmp(root->isbn, book->isbn) == 0)
		return 0;

	if(strcmp(root->isbn, book->isbn) > 0)
	{
		return insertToBST(&root->left, book);
	}
	else
	{
		return insertToBST(&root->right, book);
	}
}

int insertToArray(book* books, book* book)
{
	// strcpy checks for title and isbn were done in the previous step of insertToBST
	strcpy_s(books[booksInLibrary].title, STRSIZE, book->title);
	strcpy_s(books[booksInLibrary].author, STRSIZE, book->author);
	strcpy_s(books[booksInLibrary].isbn, 13, book->isbn);

	books[booksInLibrary].isAvailable = 1;

	return 1;
}

int searchBook(treenode* booksTree, book* bookArray, const char* identifier, int isISBN, book* out_book)
{
	int index = searchBST(booksTree, identifier, isISBN);

	// if not found return -1
	if(index == -1)
		return 0;
	else
	{
		out_book = &bookArray[index];
		return 1;
	}

}

int searchBST(treenode* booksTree, const char* identifier, int isISBN)
{
	if(booksTree == NULL) return -1;
	
	if(isISBN) // If searching with ISBN
	{
		if(strcmp(booksTree->isbn, identifier) == 0)
		{
			return booksTree->index;
		}

		if(strcmp(booksTree->isbn, identifier) > 0)
		{
			return searchBST(booksTree->left, identifier, isISBN);
		}
		else
		{
			return searchBST(booksTree->right, identifier, isISBN);
		}

	}
	else	// If searching with Title
	{
		// Not implemented
		return -1;
	}
}