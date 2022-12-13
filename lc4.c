#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


/* find a position of num in n1 */
/* n1 must be ordinal array */
#if 0
int findPostion(int* n1, int nsize, int num)
{
	int p = nsize / 2; /* position */
	if (nsize == 1) {
		if (n1[0] > num)
			return 0;
		else
			return 1;
	}

	while (n1[p - 1]  > num || n1[p]  <= num) {
		if (p - 1 < 0 || p - 1 >= nsize || p < 0 || p >= nsize) {
			printf("warning p %d\n", p);
		}

		if (p == nsize - 1) {
			p += 1;
			break;
		}

		p = (n1[p] > num) ? (p / 2) : ((p + nsize) / 2);

		if (p == 0) {
			 break;
		}
	}
	return p;
}
#else

int __findPostion(int *n1, int nsize, int num, int bias)
{
	int p = nsize / 2;

	if (p == 0) {
		if (nsize == 0 || n1[0] > num)
			return bias;
		else
			return bias + 1;
	}

	if (n1[p] > num && n1[p - 1] <= num)
		return p + bias;

	if (n1[p] > num)
		return __findPostion(n1, nsize - p - 1, num, bias);
	else
		return __findPostion(&n1[p + 1], nsize - (p + 1), num, bias + p + 1);

}

int findPostion(int* n1, int nsize, int num)
{
	if (nsize == 0)
		return 0;
	return __findPostion(n1, nsize, num, 0);
}
#endif

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

#define CASE_1
#ifdef CASE_1
void case_1(void) {
	int c1[] = { 1, 6};
	int c2[] = { 5 };
	printf("5 = %f\n", findedianSortedArrays(c1, 2, c2, 1));
}
#endif

#define CASE_2
#ifdef CASE_2
void case_2(void) {
	int c3[] = { 3, 9, 12};
	int c4[] = { 1, 6, 10, 67,};
	printf("9 = %f\n", findedianSortedArrays(c3, 3, c4, 4));
}
#endif

#define CASE_3
#ifdef CASE_3
void case_3(void)
{
	int c1[] = { 1, 1, 3};
	int c2 = 2;
	printf("2, %d\n", findPostion(c1, 3, c2));
}
#endif

#define CASE_4
#ifdef CASE_4
void case_4(void)
{
	int c1[] = { 1, 1, 3};
	int c2 = 0;
	printf("0, %d\n", findPostion(c1, 3, c2));
}
#endif

#define CASE_5
#ifdef CASE_5
void case_5(void)
{
	int c1[] = { 1, 1, 3};
	int c2 = 1;
	printf("2, %d\n", findPostion(c1, 3, c2));
}
#endif

#define CASE_6
#ifdef CASE_6
void case_6(void)
{
	int c1[] = { 1, 1, 3};
	int c2 = 3;
	printf("3, %d\n", findPostion(c1, 3, c2));
}
#endif

#define CASE_7
#ifdef CASE_7
void case_7(void)
{
	int c1[] = {1, 2};
	int c2[] = {3, 4};
	printf("2.5, %f\n", findedianSortedArrays(c1, 2, c2, 2));
}
#endif

#define CASE_8
#ifdef CASE_8
void case_8(void)
{
	int c1[] = {1};
	printf("1, %d\n", findPostion(c1, 1, 1));
	printf("0, %d\n", findPostion(c1, 1, 0));
	printf("1, %d\n", findPostion(c1, 1, 2));
}
#endif

#define CASE_9
#ifdef CASE_9
void case_9(void)
{
	int c1[] = {};
	int c2[] = {4};
	printf("4, %f\n", findedianSortedArrays(c1, 0, c2, 1));
}
#endif

#define CASE_10
#ifdef CASE_10
void case_10(void)
{
	int c1[] = {4};
	int c2[] = {4};
	printf("4, %f\n", findedianSortedArrays(c1, 1, c2, 1));
}
#endif

#define CASE_11
#ifdef CASE_11
void case_11(void)
{
	int c1[] = {2, 3};
	int c2[] = {1};
	printf("2, %f\n", findedianSortedArrays(c1, 2, c2, 1));
}
#endif

#define CASE_12
#ifdef CASE_12
void case_12(void)
{
	int c1[] = {2, 3};
	int c2 = 1;
	printf("0, %d\n", findPostion(c1, 2, c2));
}
#endif

#define CASE_13
#ifdef CASE_13
void case_13(void)
{
	int c1[] = {1, 2, 4, 5, 6, 7};
	int c2[] = {3};
	printf("4, %f\n", findedianSortedArrays(c1, 6, c2, 1));
}
#endif

int main(void)
{
#ifdef CASE_1
	case_1();
#endif

#ifdef CASE_2
	case_2();
#endif

#ifdef CASE_3
	case_3();
#endif

#ifdef CASE_4
	case_4();
#endif

#ifdef CASE_5
	case_5();
#endif

#ifdef CASE_6
	case_6();
#endif

#ifdef CASE_7
	case_7();
#endif

#ifdef CASE_8
	case_8();
#endif

#ifdef CASE_9
	case_9();
#endif

#ifdef CASE_10
	case_10();
#endif

#ifdef CASE_11
	case_11();
#endif

#ifdef CASE_12
	case_12();
#endif

#ifdef CASE_13
	case_13();
#endif
}
