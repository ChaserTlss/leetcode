#include "lcHead.h"


/* reverse the link list by group.
 * k is unsigned int, value less or eq the list link length.
 * if link length % k != 0 then keep the seq of last entry */
struct ListNode* reverseKGroup(struct ListNode* head, int k)
{
	struct ListNode ret = {.val = 0, .next = head};
	struct ListNode *cur = head;
	struct ListNode *groupHead = &ret;
	int count = 0;
	if (k == 1) {
		return head;
	}

	/* move next node to gropHead->next */
	while (cur && cur->next) {
		/* [g]->[c]->[n]->[other] */
		/* cut and insert n to g-> */
		/* [g]->[n]->[c]->[other] */
		struct ListNode *temp = cur->next;
		cur->next = temp->next;
		temp->next = groupHead->next;
		groupHead->next = temp;
		count++;

		/* case k = 2 */
		/* start       [r]->[1]->[2]->[3] */
		/* done 1 time [r]->[2]->[1]->[3] */
		/* then we need do */

		/* case k = 3 */
		/* start       [r]->[1]->[2]->[3]->[4] */
		/* done 1 time [r]->[2]->[1]->[3]->[4] */
		/* done 2 time [r]->[3]->[2]->[1]->[4] */
		/* then we need do */
		if (count >= k - 1) {
			count = 0;
			groupHead = cur;
			cur = cur->next;
		}
	}

	cur = groupHead->next;
	/* back */
	while (count-- > 0 && cur->next) {
		struct ListNode *temp = cur->next;
		cur->next = temp->next;
		temp->next = groupHead->next;
		groupHead->next = temp;
	}

	return ret.next;
}

void case_1(void)
{
	struct ListNode a1[] = { {.val = 1}, {.val = 2}, {.val = 3}, {.val = 4}, {.val = 5},};
	listGenerate(a1, ARRAYSIZE(a1));

	struct ListNode *ret = reverseKGroup(a1, 2);

	/* it should be [2]->[1]->[4]->[3]->[5] */
	int val[] = {2, 1, 4, 3, 5};
	if (!listCheck(ret, val, ARRAYSIZE(val))) {
		printf("case 1 is failed\n");
	}
}

void case_2(void)
{
	struct ListNode a1[] = { {.val = 1}, {.val = 2}, {.val = 3}, {.val = 4}, {.val = 5},};
	listGenerate(a1, ARRAYSIZE(a1));

	struct ListNode *ret = reverseKGroup(a1, 3);

	/* it should be [2]->[1]->[4]->[3]->[5] */
	int val[] = {3, 2, 1, 4, 5};
	if (!listCheck(ret, val, ARRAYSIZE(val))) {
		printf("case 2 is failed\n");
	}
}

void case_3(void)
{
	struct ListNode a1[] = { {.val = 1}, {.val = 2}, {.val = 3}, {.val = 4}, {.val = 5},};
	listGenerate(a1, ARRAYSIZE(a1));

	struct ListNode *ret = reverseKGroup(a1, 1);

	/* it should be [2]->[1]->[4]->[3]->[5] */
	int val[] = {1, 2, 3, 4, 5};
	if (!listCheck(ret, val, ARRAYSIZE(val))) {
		printf("case 3 is failed\n");
	}
}

int main(void)
{
	case_1();
	case_2();
	case_3();
	return 0;
}
