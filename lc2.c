#include "lcHead.h"

struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2)
{
	int carry = 0;
	struct ListNode ret = {.val = 0, .next = NULL};
	struct ListNode *t = &ret;

	while (l1 != NULL || l2 != NULL || carry != 0) {
		t->next = malloc(sizeof(struct ListNode));
		t = t->next;
		t->next = NULL;

		t->val = carry;
		carry = 0;
		if (l1 != NULL) {
			t->val += l1->val;
			carry = (t->val) / 10;
			t->val = t->val % 10;

			l1 = l1->next;
		}

		if (l2 != NULL) {
			t->val += l2->val;
			carry += (t->val) / 10;
			t->val = t->val % 10;

			l2 = l2->next;
		}
	}
	return ret.next;
}

void case_1(void) {
	struct ListNode l1m[3] = {
		{2, &l1m[1]},
		{4, &l1m[2]},
		{3, NULL}};
	struct ListNode l2m[3] = {
		{5, &l2m[1]},
		{6, &l2m[2]},
		{4, NULL}};

	struct ListNode *t = addTwoNumbers(l1m, l2m);

	int a[] = {7, 0, 8};
	listCheck(t, a, ARRAYSIZE(a));
	while (t) {
		struct ListNode *f = t;
		t = t->next;
		free(f);
	}
}

REGISTER_TEST_CASE(case_1);
