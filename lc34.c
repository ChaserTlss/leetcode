#include "lcHead.h"
int compGetStartPostion(const void *item, const void *key)
{
	return *(int *)item - *(int *)key + 1;
}

int compGetEndPostion(const void *item, const void *key)
{
	return *(int *)item - *(int *)key;
}

int *searchRange(int *nums, int numsSize, int target, int *returnSize)
{
	*returnSize = 2;
	int *ret = malloc(*returnSize * sizeof(int));

	ret[0] = findP(&target, nums, numsSize, sizeof(int), compGetStartPostion);
	
	if (!numsSize || ret[0] >= numsSize || nums[ret[0]] != target) {
		ret[0] = -1;
		ret[1] = -1;
		return ret;
	}

	ret[1] = findP(&target, nums + ret[0], numsSize - ret[0], sizeof(int), compGetEndPostion) - 1 + ret[0];
	return ret;
}

void case_1(void)
{
	int a[] = {5, 7, 7, 8, 8, 10};
	int target = 8;
	int key[] = {3, 4};

	int returnSize = 0;
	int *ret = searchRange(a, ARRAYSIZE(a), target, &returnSize);

	if (returnSize != 2) {
		printf("%s failed, returnSize %d should 2\n", __func__, returnSize);
		return;
	}

	for (int i = 0; i < returnSize; i++) {
		if (key[i] != ret[i]) {
			printf("%s failed, ret[%d] %d should %d\n",
					__func__, i, ret[i], key[i]);
		}
	}

	free(ret);
}

void case_2(void)
{
	int a[] = {5, 7, 7, 8, 8, 10};
	int target = 6;
	int key[] = {-1, -1};

	int returnSize = 0;
	int *ret = searchRange(a, ARRAYSIZE(a), target, &returnSize);

	if (returnSize != 2) {
		printf("%s failed, returnSize %d should 2\n", __func__, returnSize);
		return;
	}

	for (int i = 0; i < returnSize; i++) {
		if (key[i] != ret[i]) {
			printf("%s failed, ret[%d] %d should %d\n",
					__func__, i, ret[i], key[i]);
		}
	}

	free(ret);
}

void case_3(void)
{
	int a[] = {};
	int target = 6;
	int key[] = {-1, -1};

	int returnSize = 0;
	int *ret = searchRange(a, ARRAYSIZE(a), target, &returnSize);

	if (returnSize != 2) {
		printf("%s failed, returnSize %d should 2\n", __func__, returnSize);
		return;
	}

	for (int i = 0; i < returnSize; i++) {
		if (key[i] != ret[i]) {
			printf("%s failed, ret[%d] %d should %d\n",
					__func__, i, ret[i], key[i]);
		}
	}

	free(ret);
}

void case_4(void)
{
	int a[] = {2, 2};
	int target = 3;
	int key[] = {-1, -1};

	int returnSize = 0;
	int *ret = searchRange(a, ARRAYSIZE(a), target, &returnSize);

	if (returnSize != 2) {
		printf("%s failed, returnSize %d should 2\n", __func__, returnSize);
		return;
	}

	for (int i = 0; i < returnSize; i++) {
		if (key[i] != ret[i]) {
			printf("%s failed, ret[%d] %d should %d\n",
					__func__, i, ret[i], key[i]);
		}
	}

	free(ret);
}

REGISTER_TEST_CASE(case_1);
REGISTER_TEST_CASE(case_2);
REGISTER_TEST_CASE(case_3);
REGISTER_TEST_CASE(case_4);

