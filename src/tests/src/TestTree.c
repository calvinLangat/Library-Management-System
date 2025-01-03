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
	book* book = NULL;
	TEST_ASSERT_EQUAL(NULL, createNode(book));
}

void test_CreateNode_GoodBook(void)
{
	book* book = malloc(sizeof(*book));
	strcpy_s(book->title,STRSIZE,"MyBook");
	strcpy_s(book->isbn,13,"1111111111111");
	treenode* result = createNode(book);
	TEST_ASSERT_NOT_NULL(result);
	free(book);
	free(result);
}

int main(void)
{
	UNITY_BEGIN();
	RUN_TEST(test_CreateNode_NullBook);
	RUN_TEST(test_CreateNode_GoodBook);
	return UNITY_END();
}