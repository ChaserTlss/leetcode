#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct ListNode {
	int val;
	struct ListNode *next;
};
struct ListNode* mergeTwoLists(struct ListNode* list1, struct ListNode* list2){
    struct ListNode *p1 = list1;
    struct ListNode *p2 = list2;
    struct ListNode head = {.val = 0, .next = NULL};
    struct ListNode *cur = &head;

    while (p1 && p2) {
        if (!p1) {
            cur->next = p2;
            p2 = p2->next;
        } else if (!p2) {
            cur->next = p1;
            p1 = p1->next;
        } else if (p1->val < p2->val) {
            cur->next = p1;
            p1 = p1->next;
        } else {
            cur->next = p2;
            p2 = p2->next;
        }
        cur = cur->next;
    }

    if (p1 || p2) {
        if (p1) {
            cur->next = p1;
        } else {
            cur->next = p2;
        }
    }

    return head.next;
}
struct ListNode* mergeKLists(struct ListNode** lists, int listsSize){
    if (listsSize == 0)
        return NULL;

    while (listsSize > 1) {
        for (int i = 0; i < listsSize / 2; i++) {
            lists[i] = mergeTwoLists(lists[i * 2], lists[i * 2 + 1]);
        }
        if (listsSize % 2)
            lists[0] = mergeTwoLists(lists[0], lists[listsSize - 1]);
        listsSize /= 2;
    }

    return lists[0];
}

#define ARRAYSIZE(array) (sizeof(array)/sizeof(array[0]))
void listGenerate(struct ListNode array[], size_t arraySize)
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

int main(void)
{
	struct ListNode array1[3] = {{.val = 1}, {.val = 4}, {.val = 5}};
	listGenerate(array1, ARRAYSIZE(array1));
	struct ListNode array2[3] = {{.val = 1}, {.val = 3}, {.val = 4}};
	listGenerate(array2, ARRAYSIZE(array2));
	struct ListNode array3[2] = {{.val = 2}, {.val = 6}};
	listGenerate(array3, ARRAYSIZE(array3));
	struct ListNode *array0[] = {array1, array2, array3};

	struct ListNode *ret = mergeKLists(array0, ARRAYSIZE(array0));

	while (ret) {
		printf("%d\n", ret->val);
		ret = ret->next;
	}
	return 0;
}
