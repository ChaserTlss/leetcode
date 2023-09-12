#ifndef __LCHEAD__H__
#define __LCHEAD__H__
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>

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
	case_fn_t __attribute__((section ("test_case,test_fn_p"))) fn_name##_fn = fn_name
#elif __GNUC__
extern case_fn_t __start_test_fn_p;
extern case_fn_t __stop_test_fn_p;
#define REGISTER_TEST_CASE(fn_name) \
	case_fn_t __attribute__((section ("test_fn_p"))) fn_name##_fn = fn_name
#endif

int main(void)
{
	int index = 0;
	/* There is a difference between clang and gcc:
	 * What gcc offer with __start_test_fn_p is the array's start.
	 * If we try to get the address of the array's start, we will get the array's start again,
	 * They are same. array's start == array's start's address.
	 * But in clang the __start_test_fn_p is a point.
	 * point's address != point's value.
	 * I prefer use the &__start_test_fn_p to indicate I'm operating the elemnt's address.
	 * But I can not do it in clang.
	 * So we use __start_test_fn_p as point, then it can work well both in clang and gcc.
	 */

	/* YES, I want to compare the address, and they are function address, make the clang quiet */
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wordered-compare-function-pointers"
#endif
	for (case_fn_t iter = __start_test_fn_p; (iter + index) < __stop_test_fn_p; index++)
		(iter + index)();
#ifdef __clang__
#pragma clang diagnostic pop
#endif


	printf("unit test finish: count %d. pls check the log\n", index);
	return 0;
}

#endif /* #ifndef __LCHEAD__H__ */
