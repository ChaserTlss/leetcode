#include "lcHead.h"
int compare(const void *a, const void *b)
{
	return *(int *)a - *(int *)b;
}

void nextPermutation(int *nums, int numsSize)
{
    int state = 0;
    int *max = &nums[numsSize - 1];

    for (int i = numsSize - 2; i >= 0; i--) {
	    if ((i == 0 || nums[i] > nums[i - 1] || nums[i] < nums[i + 1]) && nums[i] < *max) {
		    int *minInTheGreaters = max;

		    for (int j = i + 1; j < numsSize; j++) {
			    if (nums[j] > nums[i] && nums[j] < *minInTheGreaters) {
				    minInTheGreaters = &nums[j];
			    }
		    }
		    int temp = *minInTheGreaters;
		    *minInTheGreaters = nums[i];
		    nums[i] = temp;

		    qsort(nums + i + 1, numsSize - i - 1, sizeof(nums[0]), compare);
		    return;
	    }
	    if (nums[i] > *max)
		    max = &nums[i];
    }

    qsort(nums, numsSize, sizeof(nums[0]), compare);
}

void case_1(void)
{
	int a[] = {1, 3, 2};
	int key[] = {2, 1, 3};

	nextPermutation(a, ARRAYSIZE(a));

	for (int i = 0; i < ARRAYSIZE(a); i++) {
		if (a[i] != key[i]) {
			printf("%s is failed, a[%d] is %d should %d\n",
					__func__, i, a[i], key[i]);
		}
	}
}

void case_2(void)
{
	int a[] = {1, 2, 3};
	int key[] = {1, 3, 2};

	nextPermutation(a, ARRAYSIZE(a));

	for (int i = 0; i < ARRAYSIZE(a); i++) {
		if (a[i] != key[i]) {
			printf("%s is failed, a[%d] is %d should %d\n",
					__func__, i, a[i], key[i]);
		}
	}
}

void case_3(void)
{
	int a[] = {3, 2, 1};
	int key[] = {1, 2, 3};

	nextPermutation(a, ARRAYSIZE(a));

	for (int i = 0; i < ARRAYSIZE(a); i++) {
		if (a[i] != key[i]) {
			printf("%s is failed, a[%d] is %d should %d\n",
					__func__, i, a[i], key[i]);
		}
	}
}

void case_4(void)
{
	int a[] = {1, 1, 5};
	int key[] = {1, 5, 1};

	nextPermutation(a, ARRAYSIZE(a));

	for (int i = 0; i < ARRAYSIZE(a); i++) {
		if (a[i] != key[i]) {
			printf("%s is failed, a[%d] is %d should %d\n",
					__func__, i, a[i], key[i]);
		}
	}
}

void case_5(void)
{
	int a[] = {2, 3, 1};
	int key[] = {3, 1, 2};

	nextPermutation(a, ARRAYSIZE(a));

	for (int i = 0; i < ARRAYSIZE(a); i++) {
		if (a[i] != key[i]) {
			printf("%s is failed, a[%d] is %d should %d\n",
					__func__, i, a[i], key[i]);
		}
	}
}

REGISTER_TEST_CASE(case_1);
REGISTER_TEST_CASE(case_2);
REGISTER_TEST_CASE(case_3);
REGISTER_TEST_CASE(case_4);
REGISTER_TEST_CASE(case_5);

