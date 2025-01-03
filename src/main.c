#include "library.h"


int main(int argc, char* argv[])
{
	booksInLibrary = 0;
	slotsUsed = 0;

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
	if(slotsUsed < MAXBOOKS)
	{
		// Just a placeholder
		if(!insertBook(books, &booktree, &book))
		{
			printf("Failed to insert book.\n");
		}
		else
		{
			booksInLibrary++;
		}
	}

	struct book book1;
	
	// Another placeholder
	if(!searchBook(booktree, books, "", 1, &book1))
	{
		printf("Could not find book.\n");
	}

	if(!deleteBook(&booktree, books, "", 1))
	{
		printf("Failed to delete book.\n");
	}
	else
	{
		booksInLibrary--;
	}

	return 0;
}

