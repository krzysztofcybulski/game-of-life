#ifndef GOL_C_TEST_H
#define GOL_C_TEST_H

typedef struct Test {
	char *name;
	char *should;
	void *returned;
	void *expected;
	int result;
} *test_t;

typedef struct UTests {
	test_t *tests;
	int size;
	int tests_amount;
	int result;
} *utests_t;

int test(utests_t, char *name, void *returned, void *expected);
int print_results(utests_t utests);
utests_t alloc_utests();

#endif