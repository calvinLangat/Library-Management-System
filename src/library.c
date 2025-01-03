#include "library.h"

// Globals
int booksInLibrary;
int slotsUsed;
slots_t freeSlots;


treenode_t* createNode(book_t* book)
{
	treenode_t* node = malloc(sizeof(treenode_t));
	if(node == NULL)
	{
		return NULL;
	}

	if(strcpy_s(node->title, STRSIZE, book->title) || strcpy_s(node->isbn, ISBNSIZE, book->isbn))
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

int insertBook(book_t* bookArray, treenode_t** booktree, book_t* book)
{
	// Find a spot in the Registry (tree) first before inserting to shelf (Array)
	if(insertToBST(booktree, book))
	{
		if (insertToArray(bookArray, book))
		{
			booksInLibrary++;
			return 1;
		}
		else
		{
			return 0;
		}
	}
	else
	{
		return 0;
	}
}

int insertToBST(treenode_t** bookTreeRoot, book_t* book)
{
	treenode_t* root = *bookTreeRoot;

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

int insertToArray(book_t* bookArray, book_t* book)
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
		if(slotsUsed < MAXBOOKS)
		{
			index = slotsUsed;
			slotsUsed++;
		}
		else
		{
			return 0;
		}
	}

	// strcpy checks for title and isbn were done in the previous step of insertToBST
	strcpy_s(bookArray[index].title, STRSIZE, book->title);
	strcpy_s(bookArray[index].author, STRSIZE, book->author);
	strcpy_s(bookArray[index].isbn, ISBNSIZE, book->isbn);
	bookArray[index].isAvailable = 1;
	
	return 1;
}

int searchBook(treenode_t* booksTree, book_t* bookArray, const char* identifier, int isISBN, book_t* out_book)
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

int searchBST(treenode_t* booksTree, const char* identifier, int isISBN)
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

int deleteBook(treenode_t** booksTree, book_t* bookArray, const char* identifier, int isISBN)
{
	int index = searchBST(*booksTree, identifier, isISBN);
	if(index == -1) return 0;

	int result = deleteNode(booksTree, identifier);

	if(result == -1) return 0;

	// Deletion successful, update the freeSlot record
	freeSlots.slots[freeSlots.count] = index;
	freeSlots.count++;
	booksInLibrary--;
	return 1;
}

int deleteNode(treenode_t** booksTree, const char* identifier)
{
	treenode_t* root = *booksTree;
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
			treenode_t* temp = root->right;
			free(root);
			*booksTree = temp;
		}
		// Case 2b: One child (left)
		else if(root->right == NULL)
		{
			treenode_t* temp = root->left;
			free(root);
			*booksTree = temp;
		}
		 // Case 3: Two children
		else
		{
			treenode_t* successor = getSuccessor(root->right);
			strcpy_s(root->title, STRSIZE, successor->title);
			strcpy_s(root->isbn, ISBNSIZE, successor->isbn);
			root->index = successor->index;
			return deleteNode(&root->right, successor->isbn);	
		}
		
	}
	// Node deleted successfully
	return 1;
}

treenode_t* getSuccessor(treenode_t* node)
{
	if(node == NULL)
		return NULL;

	while(node->left != NULL)
		node = node->left;

	return node;
}