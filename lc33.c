#include "lcHead.h"

ssize_t findRotatedIndex(int *nums, ssize_t numsSize, ssize_t bias)
{
	ssize_t point = numsSize / 2;

	if (point >= numsSize || numsSize < 2)
		return -1; /* rotated index is not exist */

	if (nums[point] < nums[point - 1])
		return point + bias;

	if (nums[point] > nums[0])
		return findRotatedIndex(nums + point, numsSize - point, bias + point);
	else
		return findRotatedIndex(nums, point, bias);
}

int compare(const void *a, const void *b)
{
	return *(int *)a - *(int *)b;
}

int search(int* nums, int numsSize, int target)
{
	/* 1 step: find the rotated index */
	ssize_t rotatedIndex = findRotatedIndex(nums, numsSize, 0);

	/* rotated index is not exist */
	if (rotatedIndex == -1) {
		int *targetPoint = bsearch(&target, nums, numsSize, sizeof(int), compare);
		if (!targetPoint)
			return -1;
		/* NOTE: since we use int * to cal the point,
		 * we already get the index,
		 * didnot need this format:
		 * return (targetPoint - nums) / sizeof(int) */
		return targetPoint - nums;
	}

	/* find in first array */
	int *targetPoint = bsearch(&target, nums, rotatedIndex, sizeof(int), compare);

	/* find ! */
	if (targetPoint)
		return targetPoint - nums;

	/* find in second array */
	targetPoint = bsearch(&target, nums + rotatedIndex, numsSize - rotatedIndex, sizeof(int), compare);

	if (!targetPoint)
		return -1;
	return targetPoint - nums;
}

void case_1(void)
{
	int a[] = {4, 5, 6, 7, 0, 1, 2};
	int target = 0;
	int keyRet = 4;

	int ret = search(a, ARRAYSIZE(a), target);

	if (ret != keyRet) {
		printf("%s failed, ret %d should be %d\n",
				__func__, ret, keyRet);
	}
}

void case_2(void)
{
	int a[] = {4, 5, 6, 7, 0, 1, 2};
	int target = 3;
	int keyRet = -1;

	int ret = search(a, ARRAYSIZE(a), target);

	if (ret != keyRet) {
		printf("%s failed, ret %d should be %d\n",
				__func__, ret, keyRet);
	}
}

void case_3(void)
{
	int a[] = {1};
	int target = 0;
	int keyRet = -1;

	int ret = search(a, ARRAYSIZE(a), target);

	if (ret != keyRet) {
		printf("%s failed, ret %d should be %d\n",
				__func__, ret, keyRet);
	}
}

void case_4(void)
{
	int a[] = {4, 5, 6, 7, 0, 1, 2};
	int keyIndex = 4;

	int ret = findRotatedIndex(a, ARRAYSIZE(a), 0);

	if (ret != keyIndex) {
		printf("%s failed, ret %d should be %d\n",
				__func__, ret, keyIndex);
	}
}

void case_5(void)
{
	int a[] = {1};
	int keyIndex = -1;

	int ret = findRotatedIndex(a, ARRAYSIZE(a), 0);

	if (ret != keyIndex) {
		printf("%s failed, ret %d should be %d\n",
				__func__, ret, keyIndex);
	}
}

void case_6(void)
{
	int a[] = {3, 1};
	int target = 3;
	int keyRet = 0;

	int ret = search(a, ARRAYSIZE(a), target);

	if (ret != keyRet) {
		printf("%s failed, ret %d should be %d\n",
				__func__, ret, keyRet);
	}
}

REGISTER_TEST_CASE(case_1);
REGISTER_TEST_CASE(case_2);
REGISTER_TEST_CASE(case_3);
REGISTER_TEST_CASE(case_4);
REGISTER_TEST_CASE(case_5);
REGISTER_TEST_CASE(case_6);

