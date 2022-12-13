 struct ListNode {
     int val;
     struct ListNode *next;
 };
 
#include <stdio.h>
#include <stdlib.h>


struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2){
    int carry = 0;
    struct ListNode *t = NULL;
    struct ListNode *ret = NULL;

    while (l1 != NULL || l2 != NULL || carry != 0) {
        if (t) {
            t->next = malloc(sizeof(struct ListNode));
            /* if null */
            t = t->next;
        } else {
            ret = t = malloc(sizeof(struct ListNode));
        }

        t->val = carry;
        carry = 0;
        if (l1 != NULL) {
            t->val += l1->val;
            carry += (l1->val + t->val) / 10;
            t->val = t->val % 10;
            l1 = l1->next;
        }

        if (l2 != NULL) {
            t->val += l2->val;
            carry += (l2->val + t->val) / 10;
            t->val = t->val % 10;
            l2 = l2->next;
        }
    }
    return ret;
}

int main(void) {
	struct ListNode l1m[3] = {
		{2, &l1m[1]},
		{4, &l1m[2]},
		{3, NULL}};
	struct ListNode l2m[3] = {
		{5, &l2m[1]},
		{6, &l2m[2]},
		{4, NULL}};

	struct ListNode *t = addTwoNumbers(l1m, l2m);
	return 0;
}
