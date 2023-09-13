#ifndef __LCHEAD__H__
#define __LCHEAD__H__
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>
#include <assert.h>

#include "lcBox.h"
#include "lcBox2d.h"
#include "lcBitmap.h"
#include "lcFindPostionBS.h"
#include "lcDeduplicate.h"

/* Definition for leetcode singly-linked list. */
struct ListNode {
	int val;
	struct ListNode *next;
};

/* for unit test list */
#define ARRAYSIZE(array) (sizeof(array)/sizeof(array[0]))
static void listGenerate(struct ListNode array[], size_t arraySize)
{
	if (array == NULL)
		return;

	struct ListNode *node = &array[0];
	for (int i = 1; i < arraySize; i++) {
		node->next = &array[i];
		node = node->next;
	}
	node->next = NULL;
}

static bool listCheck(struct ListNode *head, int valArray[], size_t arraySize)
{
	for (int i = 0; i < arraySize; i++) {
		if (!head) {
			printf("list is break or not enough as need [%d]/[%ld]\n", i, arraySize);
			return false;
		}
		if (head->val != valArray[i]) {
			printf("%d node's val %d is should be %d\n", i, head->val, valArray[i]);
			return false;
		}
		head = head->next;
	}
	return true;
}

/* for common unit function */
typedef void (*case_fn_t)(void);
#if __clang__
extern case_fn_t __start_test_fn_p __asm__("section$start$test_case$test_fn_p");
extern case_fn_t __stop_test_fn_p __asm__("section$end$test_case$test_fn_p");
#define REGISTER_TEST_CASE(fn_name) \
	case_fn_t __attribute__((section ("test_case,test_fn_p"))) __attribute__((no_sanitize("address"))) fn_name##_fn = fn_name
#elif __GNUC__
extern case_fn_t __start_test_fn_p;
extern case_fn_t __stop_test_fn_p;
#define REGISTER_TEST_CASE(fn_name) \
	case_fn_t __attribute__((section ("test_fn_p"))) fn_name##_fn = fn_name
#endif

int main(void)
{
	int index = 0;
	for (case_fn_t *iter = &__start_test_fn_p; (iter + index) < &__stop_test_fn_p; index++)
		(*(iter + index))();

	printf("unit test finish: count %d. pls check the log\n", index);
	return 0;
}

#endif /* #ifndef __LCHEAD__H__ */
