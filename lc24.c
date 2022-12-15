#include "lcHead.h"

struct ListNode* swapPairs(struct ListNode *head)
{
	struct ListNode retHead = {.val = 0, .next = head};
	struct ListNode *previous = &retHead;
	struct ListNode *next = NULL;
	struct ListNode *current = retHead.next;
	while (current && current->next) {
		next = current->next;

		/* [p] -> [c] -> [n] -> [another one] */
		/* exchange */
		/* [p] -> [n] -> [c] -> [another one] */
		current->next = next->next;
		next->next = current;
		previous->next = next;

		previous = current;
		current = current->next;
	}

	return retHead.next;
}

void case_1(void) {
	struct ListNode a1[] = { {.val = 1}, {.val = 2}, {.val = 3}, {.val = 4}};
	listGenerate(a1, ARRAYSIZE(a1));

	struct ListNode *ret = swapPairs(a1);

	/* check */
	/* It should be  [2]->[1]->[4]->[3] */
	int val[] = {2, 1, 4, 3};
	if (!listCheck(ret, val, ARRAYSIZE(val))) {
		printf("case 1 is failed\n");
	}

}
REGISTER_TEST_CASE(case_1);
