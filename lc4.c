#include "lcHead.h"
/* find a position of num in n1 */
/* n1 must be ordinal array */

int compare(const void *item, const void *key)
{
	return *(int *)item - *(int *)key;
}

int findPostion(int* n1, int nsize, int num)
{
	if (nsize == 0)
		return 0;
	return findPostionBS(&num, n1, nsize, sizeof(int), compare, 0);
}

int findValue(int* nums1, int nums1Size, int* nums2, int nums2Size, int k)
{
	do {
		if (nums1Size == 0) {
			return nums2[k];
		}
		if (nums2Size == 0) {
			return nums1[k];
		}

		int p2 = nums2Size / 2;
		int p1 = findPostion(nums1, nums1Size, nums2[p2]);

		if ((p1 + p2) == k) {
			return nums2[p2];
		} else if ((p1 + p2) < k) {
			k -= (p1 + p2);
			nums1 = &nums1[p1];
			nums1Size -= p1;
			nums2 = &nums2[p2];
			nums2Size -= p2;
		} else {
			nums1Size -= nums1Size - p1;
			nums2Size -= nums2Size - p2;
		}
		int *t = nums1;
		nums1 = nums2;
		nums2 = t;

		int t0 = nums1Size;
		nums1Size = nums2Size;
		nums2Size = t0;

	} while (1);
}

float findedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size)
{
	if ((nums1Size + nums2Size) % 2 == 0) {
		return ((float)findValue(nums1, nums1Size, nums2, nums2Size, (nums1Size + nums2Size) / 2)
			+ (float)findValue(nums1, nums1Size, nums2, nums2Size, (nums1Size + nums2Size) / 2 - 1)) / 2;
	} else {
		return (float)findValue(nums1, nums1Size, nums2, nums2Size, (nums1Size + nums2Size) / 2);
	}

}

void case_1(void) {
	int c1[] = { 1, 6};
	int c2[] = { 5 };
	float key = 5.0;
	float ret = findedianSortedArrays(c1, ARRAYSIZE(c1), c2, ARRAYSIZE(c2));
	if (ret != key)
		printf("%s failed: %f should be %f\n", __func__, ret, key);
}

void case_2(void) {
	int c1[] = { 3, 9, 12};
	int c2[] = { 1, 6, 10, 67,};
	float key = 9.0;
	float ret = findedianSortedArrays(c1, ARRAYSIZE(c1), c2, ARRAYSIZE(c2));
	if (ret != key)
		printf("%s failed: %f should be %f\n", __func__, ret, key);
}

void case_7(void)
{
	int c1[] = {1, 2};
	int c2[] = {3, 4};
	float key = 2.5;
	float ret = findedianSortedArrays(c1, ARRAYSIZE(c1), c2, ARRAYSIZE(c2));
	if (ret != key)
		printf("%s failed: %f should be %f\n", __func__, ret, key);
}

void case_9(void)
{
	int c1[] = {};
	int c2[] = {4};
	float key = 4.0;
	float ret = findedianSortedArrays(c1, ARRAYSIZE(c1), c2, ARRAYSIZE(c2));
	if (ret != key)
		printf("%s failed: %f should be %f\n", __func__, ret, key);
}

void case_10(void)
{
	int c1[] = {4};
	int c2[] = {4};
	float key = 4.0;
	float ret = findedianSortedArrays(c1, ARRAYSIZE(c1), c2, ARRAYSIZE(c2));
	if (ret != key)
		printf("%s failed: %f should be %f\n", __func__, ret, key);
}

void case_11(void)
{
	int c1[] = {2, 3};
	int c2[] = {1};
	float key = 2.0;
	float ret = findedianSortedArrays(c1, ARRAYSIZE(c1), c2, ARRAYSIZE(c2));
	if (ret != key)
		printf("%s failed: %f should be %f\n", __func__, ret, key);
}


void case_13(void)
{
	int c1[] = {1, 2, 4, 5, 6, 7};
	int c2[] = {3};
	float key = 4.0;
	float ret = findedianSortedArrays(c1, ARRAYSIZE(c1), c2, ARRAYSIZE(c2));
	if (ret != key)
		printf("%s failed: %f should be %f\n", __func__, ret, key);
}

REGISTER_TEST_CASE(case_1);
REGISTER_TEST_CASE(case_2);
REGISTER_TEST_CASE(case_7);
REGISTER_TEST_CASE(case_9);
REGISTER_TEST_CASE(case_10);
REGISTER_TEST_CASE(case_11);
REGISTER_TEST_CASE(case_13);

