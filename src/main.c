#include "database.h"

int main(int argc, char* argv[])
{
	booksInLibrary = 0;
	slotsUsed = 0;


	char* file = "..\\testdata\\books.csv";
	// Use array to store the book structs
	book_t* booksArray = malloc(MAXBOOKS*sizeof(book_t));
	if(booksArray == NULL)
	{
		printf("Failed to heap allocate memory for book array.\n");
		return EXIT_FAILURE;
	}

	// Use Binary search tree to store indicies to the array
	treenode_t* booktree = NULL;	// Let insertToBST be responsible for initializing it

	book_t book = {0};

	// Just a placeholder
	// if(!insertBook(booksArray, &booktree, &book))
	// {
	// 	printf("Failed to insert book.\n");
	// }


	if(!insertBooksFromCSV(file, &booktree, booksArray))
	{
		printf("Error inserting book to Database.\n");
	}
	printf("books in lib %d\n", booksInLibrary);
	book_t book1;
	
	// Another placeholder
	if(!searchBook(booktree, booksArray, "6512177277062", 1, &book1))
	{
		printf("Could not find book title: %s.\n", book1.title);
	}
	else
	{
		printf("Found book title: %s.\n", book1.title);
	}

	if(!deleteBook(&booktree, booksArray, "6512177277062", 1))
	{
		printf("Failed to delete book.\n");
	}
	else
	{
		printf("Delete successful.\n");
	}

	if(!searchBook(booktree, booksArray, "6512177277062", 1, &book1))
	{
		printf("Could not find book title: %s.\n", book1.title);
	}
	else
	{
		printf("Found book title: %s.\n", book1.title);
	}


	return 0;
}

