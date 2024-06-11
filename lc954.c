#include "lcHead.h"
#define MAX_SIZE 100000

bool canReorderDoubled(int* arr, int arrSize)
{
	int hash_p[MAX_SIZE] = {0};
	int hash_n[MAX_SIZE] = {0};
	int zero = 0;

	for (int i = 0; i < arrSize; i++) {
		if (arr[i] == 0) zero += 1;
		else if (arr[i] > 0) hash_p[arr[i] - 1] += 1;
		else hash_n[abs(arr[i]) - 1] += 1;
	}

	if (zero % 2) return false;

	for (int i = 0; i < (MAX_SIZE - 1) / 2; i++) {
		if (hash_p[i] > hash_p[i * 2 + 1] || hash_n[i] > hash_n[i * 2 + 1]) {
			return false;
		}
		hash_p[i * 2 + 1] -= hash_p[i];
		hash_n[i * 2 + 1] -= hash_n[i];
	}

	for (int i = (MAX_SIZE - 1) / 2; i < MAX_SIZE; i++) {
		if (hash_p[i] != 0 || hash_n[i] != 0) return false;
		
	}
		
	return true;
}

void case_3(void)
{
	int arr[] = {4, -2, 2, -4};
	int arrSize = ARRAYSIZE(arr);
	bool key = true;

	assert(canReorderDoubled(arr, arrSize) == key);
}

void case_4(void)
{
	int arr[] = {10, 20, 40, 80};
	int arrSize = ARRAYSIZE(arr);
	bool key = true;

	assert(canReorderDoubled(arr, arrSize) == key);
}

REGISTER_TEST_CASE(case_3);
REGISTER_TEST_CASE(case_4);
