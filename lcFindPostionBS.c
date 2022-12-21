#include "lcHead.h"

/* this compare will get the last postion */
int compare(const void *item, const void *key)
{
	int r = *(int *)item - *(int *)key;

	return r;
}

/* this compare will get the first postion */
int compareF(const void *item, const void *key)
{
	int r = *(int *)item - *(int *)key;

	return r + 1;
}


void case_1(void)
{
	int a[] = {1, 2, 3};
	int key = 1;

	size_t i = findP(&key, a, ARRAYSIZE(a), sizeof(a[0]), compare);
	if (a[i - 1] != key) {
		printf("%s failed: i %ld, items %d, key %d\n",
				__func__, i, a[i], key);
	}
}

void case_2(void)
{
	int a[] = {1, 2, 3};
	int key = 2;

	size_t i = findP(&key, a, ARRAYSIZE(a), sizeof(a[0]), compare);
	if (a[i - 1] != key) {
		printf("%s failed: i %ld, items %d, key %d\n",
				__func__, i, a[i], key);
	}
}

void case_3(void)
{
	int a[] = {1, 2, 3};
	int key = 3;

	size_t i = findP(&key, a, ARRAYSIZE(a), sizeof(a[0]), compare);
	if (a[i - 1] != key) {
		printf("%s failed: i %ld, items %d, key %d\n",
				__func__, i, a[i], key);
	}
}

void case_4(void)
{
	int a[] = {1, 2, 3};
	int key = 0;
	size_t rightPostion = 0;

	size_t i = findP(&key, a, ARRAYSIZE(a), sizeof(a[0]), compare);
	if (i != rightPostion) {
		printf("%s failed: i %ld should be %ld\n",
				__func__, i, rightPostion);
	}
}

void case_5(void)
{
	int a[] = {1, 2, 3};
	int key = 4;
	size_t rightPostion = 3;

	size_t i = findP(&key, a, ARRAYSIZE(a), sizeof(a[0]), compare);
	if (i != rightPostion) {
		printf("%s failed: i %ld should be %ld\n",
				__func__, i, rightPostion);
	}
}

void case_6(void)
{
	int a[] = {1, 2, 2, 3};
	int key = 2;
	size_t rightPostion = 3;

	size_t i = findP(&key, a, ARRAYSIZE(a), sizeof(a[0]), compare);
	if (i != rightPostion) {
		printf("%s failed: i %ld should be %ld\n",
				__func__, i, rightPostion);
	}
}

void case_7(void)
{
	int a[] = {1, 2, 3};
	int key = 1;

	size_t i = findP(&key, a, ARRAYSIZE(a), sizeof(a[0]), compareF);
	if (a[i] != key) {
		printf("%s failed: i %ld, items %d, key %d\n",
				__func__, i, a[i], key);
	}
}

void case_8(void)
{
	int a[] = {1, 2, 3};
	int key = 2;

	size_t i = findP(&key, a, ARRAYSIZE(a), sizeof(a[0]), compareF);
	if (a[i] != key) {
		printf("%s failed: i %ld, items %d, key %d\n",
				__func__, i, a[i], key);
	}
}

void case_9(void)
{
	int a[] = {1, 2, 3};
	int key = 3;

	size_t i = findP(&key, a, ARRAYSIZE(a), sizeof(a[0]), compareF);
	if (a[i] != key) {
		printf("%s failed: i %ld, items %d, key %d\n",
				__func__, i, a[i], key);
	}
}

void case_10(void)
{
	int a[] = {1, 2, 3};
	int key = 0;
	size_t rightPostion = 0;

	size_t i = findP(&key, a, ARRAYSIZE(a), sizeof(a[0]), compareF);
	if (i != rightPostion) {
		printf("%s failed: i %ld should be %ld\n",
				__func__, i, rightPostion);
	}
}

void case_11(void)
{
	int a[] = {1, 2, 3};
	int key = 4;
	size_t rightPostion = 3;

	size_t i = findP(&key, a, ARRAYSIZE(a), sizeof(a[0]), compareF);
	if (i != rightPostion) {
		printf("%s failed: i %ld should be %ld\n",
				__func__, i, rightPostion);
	}
}

void case_12(void)
{
	int a[] = {1, 2, 2, 3};
	int key = 2;
	size_t rightPostion = 1;

	size_t i = findP(&key, a, ARRAYSIZE(a), sizeof(a[0]), compareF);
	if (i != rightPostion) {
		printf("%s failed: i %ld should be %ld\n",
				__func__, i, rightPostion);
	}
}

void case_13(void)
{
	int a[] = {1, 2,};
	int key = 1;
	size_t rightPostion = 0;

	size_t i = findP(&key, a, ARRAYSIZE(a), sizeof(a[0]), compareF);
	if (i != rightPostion) {
		printf("%s failed: i %ld should be %ld\n",
				__func__, i, rightPostion);
	}
}

REGISTER_TEST_CASE(case_1);
REGISTER_TEST_CASE(case_2);
REGISTER_TEST_CASE(case_3);
REGISTER_TEST_CASE(case_4);
REGISTER_TEST_CASE(case_5);
REGISTER_TEST_CASE(case_6);
REGISTER_TEST_CASE(case_7);
REGISTER_TEST_CASE(case_8);
REGISTER_TEST_CASE(case_9);
REGISTER_TEST_CASE(case_10);
REGISTER_TEST_CASE(case_11);
REGISTER_TEST_CASE(case_12);
REGISTER_TEST_CASE(case_13);

