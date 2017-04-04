#include "test/test.h"
#include "utils/colors.h"

#include <stdlib.h>
#include <stdio.h>

utests_t alloc_utests() {
	utests_t utests = (utests_t) malloc(sizeof(struct UTests));
	utests->tests = (test_t*) malloc(sizeof(test_t));
	utests->size = 1;
	utests->tests_amount = 0;
	utests->result = 1;
	return utests;
}

int test(utests_t utests, char *name, void *returned, void *expected) {
	test_t test_c = (test_t) malloc(sizeof(struct Test));
	test_c->name = name;
	test_c->expected = expected;
	test_c->returned = returned;
	
	test_c->result = expected == returned ? 1 : 0;
	
	if(utests->size < utests->tests_amount) {
		utests->size = utests->size * 2;
		utests->tests = (test_t*) realloc(utests->tests, sizeof(test_t) * utests->size);
	}	
	utests->tests[utests->tests_amount++] = test_c;
	
	return test_c->result;
}

int print_results(utests_t utests) {
	int i;
	
	for(i = 0; i < utests->tests_amount; i++) {
		test_t test_c = utests->tests[i];
		if(test_c->result)
			printf("%s%s works great%s\n", KGRN, test_c->name, KNRM);
		else {
			printf("%s%s should be %p, but is %p%s\n", KRED, test_c->name, test_c->expected, test_c->returned, KNRM);
			utests->result = 0;
		}
	}
	
	return utests->result;
}