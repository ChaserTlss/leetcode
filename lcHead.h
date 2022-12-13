#ifndef __LCHEAD__H__
#define __LCHEAD__H__
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

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

#endif /* #ifndef __LCHEAD__H__ */
