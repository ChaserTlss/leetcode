#include "lcHead.h"

/* Question:
Given an unsorted integer array nums, return the smallest missing positive integer.

You must implement an algorithm that runs in O(n) time and uses constant extra space.

Constraints:

1 <= nums.length <= 105
-231 <= nums[i] <= 231 - 1
*/

int firstMissingPositive(int *nums, int numsSize)
{
	/* NOTE: we do not need whole INT_MAX space, we just need numsSize + 1 space size.
	 * There are two condition:
	 * 1. if nums fill whole numsSize space, than the less nums is numsSize + 1.
	 * 2. another way, if nums[x] > numsSize, the result must < numsSize.
	 */
	struct bitmap *bitmap = newBitmap(numsSize + 1);
	setAllBitmap(bitmap, true);

	for (int i = 0; i < numsSize; i++) {
		if (nums[i] > 0 && nums[i] <= numsSize)
			clearBitmap(bitmap, nums[i] - 1);
	}

	int ret = ffsBitmap(bitmap) + 1;

	free(bitmap);
	return ret;
}

void case_1(void)
{
	int nums[] = {1, 2, 0};
	int key = 3;

	int ret = firstMissingPositive(nums, ARRAYSIZE(nums));
	if (ret != key) {
		printf("%s failed, ret is %d, should be key %d\n",
				__func__, ret, key);
	}
}
REGISTER_TEST_CASE(case_1);

void case_2(void)
{
	int nums[] = {3, 4, -1, 1};
	int key = 2;

	int ret = firstMissingPositive(nums, ARRAYSIZE(nums));
	if (ret != key) {
		printf("%s failed, ret is %d, should be key %d\n",
				__func__, ret, key);
	}
}
REGISTER_TEST_CASE(case_2);

void case_3(void)
{
	int nums[] = {7, 8, 9, 11, 12};
	int key = 1;

	int ret = firstMissingPositive(nums, ARRAYSIZE(nums));
	if (ret != key) {
		printf("%s failed, ret is %d, should be key %d\n",
				__func__, ret, key);
	}
}
REGISTER_TEST_CASE(case_3);

void case_4(void)
{
	int nums[] = {0, -1, 3, 1};
	int key = 2;

	int ret = firstMissingPositive(nums, ARRAYSIZE(nums));
	if (ret != key) {
		printf("%s failed, ret is %d, should be key %d\n",
				__func__, ret, key);
	}
}
REGISTER_TEST_CASE(case_4);

