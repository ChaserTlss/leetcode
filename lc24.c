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

#define CASE_1
#ifdef CASE_1
void case_1(void) {
	struct ListNode a1[] = { {.val = 1}, {.val = 2}, {.val = 3}, {.val = 4}};
	listGenerate(a1, ARRAYSIZE(a1));

	struct ListNode *ret = swapPairs(a1);

	/* check */
	/* It should be  [2]->[1]->[4]->[3] */
	if (ret->val != 2)
		printf(" first node is %d, should be 2\n", ret->val);

	if (ret->next->val != 1)
		printf(" first node is %d, should be 1\n", ret->next->val);

	if (ret->next->next->val != 4)
		printf(" first node is %d, should be 4\n", ret->next->next->val);

	if (ret->next->next->next->val != 3)
		printf(" first node is %d, should be 3\n", ret->next->next->next->val);

}
#endif


int main(void)
{
#ifdef CASE_1
	case_1();
#endif
}
