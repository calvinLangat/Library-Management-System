#include "../Unity/src/unity.h"
#include "../../library.h"


void setUp(void)
{
}

void tearDown(void)
{
}

// ==========================================
// Tests for Create Node
void test_CreateNode_NullBook(void)
{
	book_t* book = NULL;
	
	TEST_ASSERT_EQUAL(NULL, createNode(book));
}

void test_CreateNode_GoodBook(void)
{
	book_t* book = malloc(sizeof(*book));
	strcpy_s(book->title, STRSIZE, "MyBook");
	strcpy_s(book->isbn, ISBNSIZE, "1111111111111");
	treenode_t* result = createNode(book);

	TEST_ASSERT_NOT_NULL(result);
	
	free(book);
	free(result);
}

// ==========================================
// Tests to Insert to BST
void test_InsertToBST_NullRoot(void)
{
	treenode_t* booktree = NULL;
	book_t book = {0};
	strcpy_s(book.title, STRSIZE, "MyBook");
	strcpy_s(book.isbn, ISBNSIZE, "1111111111111");

	TEST_ASSERT(insertToBST(&booktree, &book));

	free(booktree);
}

void test_InsertToBST_NullRoot_DuplicateBook(void)
{
	treenode_t* booktree = NULL;
	book_t book = {0};
	strcpy_s(book.title, STRSIZE, "MyBook");
	strcpy_s(book.isbn, ISBNSIZE, "1111111111111");

	TEST_ASSERT(insertToBST(&booktree, &book));
	TEST_ASSERT_FALSE(insertToBST(&booktree, &book));

	free(booktree);
}

void test_InsertToBST_NullRoot_BookIsbnLess(void)
{
	treenode_t* booktree = NULL;
	book_t book = {0};
	book_t book2 = {0};
	strcpy_s(book.title, STRSIZE, "MyBook");
	strcpy_s(book.isbn, ISBNSIZE, "1111111111111");
	strcpy_s(book2.title, STRSIZE, "MyBook2");
	strcpy_s(book2.isbn, ISBNSIZE, "1111111111110");

	TEST_ASSERT(insertToBST(&booktree, &book));
	TEST_ASSERT(insertToBST(&booktree, &book2));

	free(booktree);
}

void test_InsertToBST_NullRoot_BookIsbnGreater(void)
{
	treenode_t* booktree = NULL;
	book_t book = {0};
	book_t book2 = {0};
	strcpy_s(book.title, STRSIZE, "MyBook");
	strcpy_s(book.isbn, ISBNSIZE, "1111111111111");
	strcpy_s(book2.title, STRSIZE, "MyBook2");
	strcpy_s(book2.isbn, ISBNSIZE, "1111111111112");

	TEST_ASSERT(insertToBST(&booktree, &book));
	TEST_ASSERT(insertToBST(&booktree, &book2));

	free(booktree);
}

// ==========================================
// Tests to Search in BST
void test_SearchBST_NotExists(void)
{
	treenode_t* booktree = NULL;
	book_t book = {0};
	book_t book2 = {0};
	int result = 0;
	strcpy_s(book.title, STRSIZE, "MyBook");
	strcpy_s(book.isbn, ISBNSIZE, "1111111111111");
	strcpy_s(book2.title, STRSIZE, "MyBook2");
	strcpy_s(book2.isbn, ISBNSIZE, "1111111111112");

	TEST_ASSERT(insertToBST(&booktree, &book));
	TEST_ASSERT(insertToBST(&booktree, &book2));

	result = searchBST(booktree, "1111111111115",1);
	TEST_ASSERT(result == -1);

	free(booktree);
}

void test_SearchBST_Exists(void)
{
	treenode_t* booktree = NULL;
	book_t book = {0};
	int result = -1;
	strcpy_s(book.title, STRSIZE, "MyBook");
	strcpy_s(book.isbn, ISBNSIZE, "1111111111111");
	
	TEST_ASSERT(insertToBST(&booktree, &book));

	result = searchBST(booktree, "1111111111111",1);
	TEST_ASSERT(result == 0);

	free(booktree);
}

// ==========================================
// Tests to Delete in BST
void test_DeleteNode_Null(void)
{
	treenode_t* booktree = NULL;
	int result = 0;
	result = deleteNode(&booktree, "1111111111111");
	
	TEST_ASSERT(result == -1);

	free(booktree);
}

void test_DeleteNode_OneNode(void)
{
	treenode_t* booktree = NULL;
	book_t book = {0};
	int result = -1;
	strcpy_s(book.title, STRSIZE, "MyBook");
	strcpy_s(book.isbn, ISBNSIZE, "1111111111111");
	
	TEST_ASSERT(insertToBST(&booktree, &book));

	result = deleteNode(&booktree, "1111111111111");
	TEST_ASSERT(result == 1);
	result = searchBST(booktree, "1111111111111",1);
	TEST_ASSERT(result == -1);

	free(booktree);
}

void test_DeleteNode_WithLeftChild(void)
{
	treenode_t* booktree = NULL;
	book_t book = {0};
	book_t book2 = {0};
	int result = -1;
	strcpy_s(book.title, STRSIZE, "MyBook");
	strcpy_s(book.isbn, ISBNSIZE, "1111111111111");
	strcpy_s(book2.title, STRSIZE, "MyBook2");
	strcpy_s(book2.isbn, ISBNSIZE, "1111111111110");

	TEST_ASSERT(insertToBST(&booktree, &book));
	TEST_ASSERT(insertToBST(&booktree, &book2));

	result = deleteNode(&booktree, "1111111111110");
	TEST_ASSERT(result == 1);
	result = searchBST(booktree, "1111111111110",1);
	TEST_ASSERT(result == -1);
	result = searchBST(booktree, "1111111111111",1);
	TEST_ASSERT(result != -1);

	free(booktree);
}

void test_DeleteNode_WithRightChild(void)
{
	treenode_t* booktree = NULL;
	book_t book = {0};
	book_t book2 = {0};
	int result = -1;
	strcpy_s(book.title, STRSIZE, "MyBook");
	strcpy_s(book.isbn, ISBNSIZE, "1111111111111");
	strcpy_s(book2.title, STRSIZE, "MyBook2");
	strcpy_s(book2.isbn, ISBNSIZE, "1111111111112");

	TEST_ASSERT(insertToBST(&booktree, &book));
	TEST_ASSERT(insertToBST(&booktree, &book2));

	result = deleteNode(&booktree, "1111111111112");
	TEST_ASSERT(result == 1);
	result = searchBST(booktree, "1111111111112",1);
	TEST_ASSERT(result == -1);
	result = searchBST(booktree, "1111111111111",1);
	TEST_ASSERT(result != -1);


	free(booktree);
}

void test_DeleteNode_WithBothChildren(void)
{
	treenode_t* booktree = NULL;
	book_t book = {0};
	book_t book2 = {0};
	book_t book3 = {0};
	int result = -1;
	strcpy_s(book.title, STRSIZE, "MyBook");
	strcpy_s(book.isbn, ISBNSIZE, "1111111111111");
	strcpy_s(book2.title, STRSIZE, "MyBook2");
	strcpy_s(book2.isbn, ISBNSIZE, "1111111111110");
	strcpy_s(book3.title, STRSIZE, "MyBook3");
	strcpy_s(book3.isbn, ISBNSIZE, "1111111111112");

	TEST_ASSERT(insertToBST(&booktree, &book));
	TEST_ASSERT(insertToBST(&booktree, &book2));
	TEST_ASSERT(insertToBST(&booktree, &book3));

	result = deleteNode(&booktree, "1111111111111");
	TEST_ASSERT(result == 1);

	result = deleteNode(&booktree, "1111111111112");
	TEST_ASSERT(result == 1);
	
	result = searchBST(booktree, "1111111111111",1);
	TEST_ASSERT(result == -1);
	result = searchBST(booktree, "1111111111112",1);
	TEST_ASSERT(result == -1);
	result = searchBST(booktree, "1111111111110",1);
	TEST_ASSERT(result != -1);

	free(booktree);
}

// ==========================================
// Tests to Insert to Array

void test_insertToArray_EmptyArray(void)
{
	book_t* books = malloc(10*sizeof(book_t));
	book_t book = {0};

	strcpy_s(book.title, STRSIZE, "MyBook");
	strcpy_s(book.isbn, ISBNSIZE, "1111111111111");

	TEST_ASSERT(insertToArray(books, &book));
	TEST_ASSERT(slotsUsed == 1);
	TEST_ASSERT(strcmp(books[0].isbn,"1111111111111") == 0);

	free(books);
}

void test_insertBookFull_EmptyArray(void)
{
	booksInLibrary = 0;
	slotsUsed = 0;
	freeSlots.count = 0;
	
	treenode_t* booktree = NULL;
	book_t* books = malloc(10*sizeof(book_t));

	book_t book = {0};
	strcpy_s(book.title, STRSIZE, "MyBook");
	strcpy_s(book.isbn, ISBNSIZE, "1111111111111");	
	TEST_ASSERT(insertBook(books, &booktree, &book));
	TEST_ASSERT(freeSlots.count == 0);
	TEST_ASSERT(booksInLibrary == 1);
	TEST_ASSERT(slotsUsed == 1);

	free(booktree);
	free(books);
}


void test_SearchBookFull_EmptyArray(void)
{
	booksInLibrary = 0;
	slotsUsed = 0;
	freeSlots.count = 0;
	
	treenode_t* booktree = NULL;
	book_t* books = malloc(10*sizeof(book_t));

	book_t book = {0};
	strcpy_s(book.title, STRSIZE, "MyBook");
	strcpy_s(book.isbn, ISBNSIZE, "1111111111111");	
	TEST_ASSERT(insertBook(books, &booktree, &book));
	TEST_ASSERT(freeSlots.count == 0);
	TEST_ASSERT(booksInLibrary == 1);
	TEST_ASSERT(slotsUsed == 1);

	book_t outBook = {0};
	TEST_ASSERT(searchBook(booktree, books, "1111111111111", 1, &outBook));
	TEST_ASSERT(strcmp(book.isbn, outBook.isbn) == 0);


	free(booktree);
	free(books);
}

void test_SearchBookFull_NonEmptyArray(void)
{
	booksInLibrary = 0;
	slotsUsed = 0;
	freeSlots.count = 0;
	
	treenode_t* booktree = NULL;
	book_t* books = malloc(10*sizeof(book_t));

	book_t book = {0};
	strcpy_s(book.title, STRSIZE, "MyBook");
	strcpy_s(book.isbn, ISBNSIZE, "1111111111111");	
	TEST_ASSERT(insertBook(books, &booktree, &book));
	strcpy_s(book.title, STRSIZE, "MyBook3");
	strcpy_s(book.isbn, ISBNSIZE, "1111111111112");
	TEST_ASSERT(insertBook(books, &booktree, &book));
	TEST_ASSERT(freeSlots.count == 0);
	TEST_ASSERT(booksInLibrary == 2);
	TEST_ASSERT(slotsUsed == 2);

	book_t outBook = {0};
	TEST_ASSERT(searchBook(booktree, books, "1111111111112", 1, &outBook));
	TEST_ASSERT(strcmp("MyBook3", outBook.title) == 0);


	free(booktree);
	free(books);
}


void test_DeleteBookFull_Null(void)
{
	booksInLibrary = 0;
	slotsUsed = 0;
	freeSlots.count = 0;

	treenode_t* booktree = NULL;
	book_t* books = malloc(10*sizeof(book_t));

	TEST_ASSERT_FALSE(deleteBook(&booktree, books, "1111111111112", 1));

}

void test_DeleteBookFull_Populated(void)
{
	booksInLibrary = 0;
	slotsUsed = 0;
	freeSlots.count = 0;
	
	treenode_t* booktree = NULL;
	book_t* books = malloc(10*sizeof(book_t));

	book_t book = {0};
	strcpy_s(book.title, STRSIZE, "MyBook");
	strcpy_s(book.isbn, ISBNSIZE, "1111111111111");	
	TEST_ASSERT(insertBook(books, &booktree, &book));
	strcpy_s(book.title, STRSIZE, "MyBook3");
	strcpy_s(book.isbn, ISBNSIZE, "1111111111112");
	TEST_ASSERT(insertBook(books, &booktree, &book));
	TEST_ASSERT(freeSlots.count == 0);
	TEST_ASSERT(booksInLibrary == 2);
	TEST_ASSERT(slotsUsed == 2);

	book_t outBook = {0};
	TEST_ASSERT(searchBook(booktree, books, "1111111111112", 1, &outBook));
	TEST_ASSERT(strcmp("MyBook3", outBook.title) == 0);

	TEST_ASSERT(deleteBook(&booktree, books, "1111111111112", 1));
	TEST_ASSERT(freeSlots.count == 1);
	TEST_ASSERT(booksInLibrary == 1);
	TEST_ASSERT(slotsUsed == 2);		// Didn't change
	TEST_ASSERT_FALSE(searchBook(booktree, books, "1111111111112", 1, &outBook));

	free(booktree);
	free(books);
}

int main(void)
{
	UNITY_BEGIN();

	// Testing BST
	RUN_TEST(test_CreateNode_NullBook);
	RUN_TEST(test_CreateNode_GoodBook);
	RUN_TEST(test_InsertToBST_NullRoot);
	RUN_TEST(test_InsertToBST_NullRoot_DuplicateBook);
	RUN_TEST(test_InsertToBST_NullRoot_BookIsbnLess);
	RUN_TEST(test_InsertToBST_NullRoot_BookIsbnGreater);
	RUN_TEST(test_SearchBST_NotExists);
	RUN_TEST(test_SearchBST_Exists);
	RUN_TEST(test_DeleteNode_Null);
	RUN_TEST(test_DeleteNode_OneNode);
	RUN_TEST(test_DeleteNode_WithLeftChild);
	RUN_TEST(test_DeleteNode_WithRightChild);
	RUN_TEST(test_DeleteNode_WithBothChildren);

	// Testing Array
	RUN_TEST(test_insertToArray_EmptyArray);

	// Testing insert/search/delete for both tree and array
	RUN_TEST(test_insertBookFull_EmptyArray);
	RUN_TEST(test_SearchBookFull_EmptyArray);
	RUN_TEST(test_SearchBookFull_NonEmptyArray);
	RUN_TEST(test_DeleteBookFull_Null);
	RUN_TEST(test_DeleteBookFull_Populated);

	return UNITY_END();
}