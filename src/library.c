#include "library.h"

// Globals
int booksInLibrary;
int slotsUsed;
slots freeSlots;


treenode* createNode(book* book)
{
	treenode* node = malloc(sizeof(treenode));
	if(node == NULL)
	{
		return NULL;
	}

	if(strcpy_s(node->title, STRSIZE, book->title) || strcpy_s(node->isbn, STRSIZE, book->isbn))
	{
		// If setting the title and isbn throws an error
		free(node);
		return NULL;
	}
	
	int index = 0;
	if(freeSlots.count > 0)
	{
		index = freeSlots.slots[freeSlots.count-1];
	}
	else
	{
		index = slotsUsed;
	}

	node->index = index;
	node->left = NULL;
	node->right = NULL;

	return node;
}

int insertBook(book* books, treenode** booktree, book* book)
{
	// Find a spot in the Registry (tree) first before inserting to shelf (Array)
	if(insertToBST(booktree, book))
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
	int index = 0;
	// Check if we have empty slots in array from previous deletions and use that slot
	if(freeSlots.count > 0)
	{
		index = freeSlots.slots[freeSlots.count-1];
		freeSlots.slots[freeSlots.count-1] = -1;
		freeSlots.count--;	
	}
	else
	{
		index = slotsUsed;
		slotsUsed++;
	}

	// strcpy checks for title and isbn were done in the previous step of insertToBST
	strcpy_s(books[index].title, STRSIZE, book->title);
	strcpy_s(books[index].author, STRSIZE, book->author);
	strcpy_s(books[index].isbn, 13, book->isbn);
	books[index].isAvailable = 1;
	
	return 1;
}

int searchBook(treenode* booksTree, book* bookArray, const char* identifier, int isISBN, book* out_book)
{
	int index = searchBST(booksTree, identifier, isISBN);

	// if return index is -1 return zero
	if(index == -1)
	{
		return 0;
	}
	else
	{
		*out_book = bookArray[index];
		return 1;
	}
}

int searchBST(treenode* booksTree, const char* identifier, int isISBN)
{
	// if not found return -1
	if(booksTree == NULL) return -1;
	
	// If searching with ISBN
	if(isISBN)
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
	// If searching with Title
	else
	{
		// Not implemented
		return -1;
	}
}

int deleteBook(treenode** booksTree, book* bookArray, const char* identifier, int isISBN)
{
	int index = searchBST(*booksTree, identifier, isISBN);
	if(index == -1) return 0;

	int result = deleteNode(booksTree, identifier);

	if(result == -1) return 0;

	// Deletion successful, update the freeSlot record
	freeSlots.slots[freeSlots.count] = index;
	freeSlots.count++;

	return 1;
}

int deleteNode(treenode** booksTree, const char* identifier)
{
	treenode* root = *booksTree;
	if(root == NULL)
	{
		return -1;
	}

	if(strcmp(root->isbn, identifier) < 0)
	{
		 // Recurse into the right subtree
		deleteNode(&root->right, identifier);
	}
	else if(strcmp(root->isbn, identifier) > 0)
	{
		 // Recurse into the left subtree
		deleteNode(&root->left, identifier);
	}
	else
	{
		// Found the node to delete
		// Case 1: No children
		if(root->left == NULL && root->right == NULL)
		{
			free(root);
			*booksTree = NULL;
		}
		// Case 2a: One child (right)
		else if(root->left == NULL)
		{
			treenode* temp = root->right;
			free(root);
			*booksTree = temp;
		}
		// Case 2b: One child (left)
		else if(root->right == NULL)
		{
			treenode* temp = root->left;
			free(root);
			*booksTree = temp;
		}
		 // Case 3: Two children
		else
		{
			treenode* successor = getSuccessor(root->right);
			strcpy_s(root->title, STRSIZE, successor->title);
			strcpy_s(root->isbn, STRSIZE, successor->isbn);
			root->index = successor->index;
			return deleteNode(&root->right, successor->isbn);	
		}
		
	}
	// Node deleted successfully
	return 1;
}

treenode* getSuccessor(treenode* node)
{
	if(node == NULL)
		return NULL;

	while(node->left != NULL)
		node = node->left;

	return node;
}