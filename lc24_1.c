#include "lcHead.h"
#define NLC25
#include "lc25.c"
#undef NLC25

/* can we think this question as a espically version of lc25? YES! we can */
struct ListNode* swapPairs(struct ListNode *head)
{
	return reverseKGroup(head, 2);
}

#define CASE_1
#ifdef CASE_1
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
#endif


int main(void)
{
#ifdef CASE_1
	case_1();
#endif
}
