#include "../Unity/src/unity.h"
#include "../../library.h"


void setUp(void)
{
}

void tearDown(void)
{
}

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


int main(void)
{
	UNITY_BEGIN();
	RUN_TEST(test_CreateNode_NullBook);
	RUN_TEST(test_CreateNode_GoodBook);
	RUN_TEST(test_InsertToBST_NullRoot);
	RUN_TEST(test_InsertToBST_NullRoot_DuplicateBook);
	RUN_TEST(test_InsertToBST_NullRoot_BookIsbnLess);
	return UNITY_END();
}