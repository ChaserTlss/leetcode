#include "lcHead.h"

void case_1(void)
{
	/* -1 is end */
	int a[][6] = {  {1, 2, 3, 4, 5, -1},
			{4, 5, 6, 7, -1},
			{1, -1},
			{3, 4, 5, 6, -1},
	};
	struct box2d *box2d = newBox2d(sizeof(int));

	for (int i = 0; i < ARRAYSIZE(a); i++) {
		for (int j = 0; j < ARRAYSIZE(a[0]);j++) {
			if (a[i][j] == -1)
				break;
			int  *ret = inputBox2d(box2d, &a[i][j], i);
			if (*ret != a[i][j])
				printf("%s is failed, inputBox2d return %p value %d, value should be %d\n",
						__func__, ret, *ret, a[i][j]);
			
		}
	}
	size_t size = 0;
	size_t *colSize = NULL;
	int **ret = NULL;

	ret = expectBox2d(box2d, &size, &colSize);
	if (size != ARRAYSIZE(a)) {
		printf("%s is failed, size %ld should be %ld\n",
				__func__, size, ARRAYSIZE(a));
	}

	for (int i = 0; i < size; i++) {
		if (colSize[i] > ARRAYSIZE(a[0])) {
			printf("%s is failed, colsize[%d] %ld is larger than %ld\n",
					__func__, i, colSize[i], ARRAYSIZE(a[0]));
			continue;
		}
		for (int j = 0; j < colSize[i]; j++) {
			if (a[i][j] == -1) {
				printf("%s is failed, colsize[%d] %ld is bigger than real size\n",
						__func__, i, colSize[i]);
				break;
			}
			if (a[i][j] != ret[i][j]) {
				printf("%s is failed, table[%d][%d] is %d should be %d\n",
						__func__, i, j, ret[i][j], a[i][j]);
			}
		}
		free(ret[i]);
	}
	free(ret);
	free(colSize);
}
REGISTER_TEST_CASE(case_1);

void case_2(void)
{
	int a[][3] = {{1, 2, 3}, {4, 5, 6}};
	struct box2d *box2d = newBox2d(sizeof(int));
	size_t keyRetSize = 1;
	int delIndex = 0;

	for (size_t i = 0; i < ARRAYSIZE(a); i++) {
		for (size_t j = 0; j < ARRAYSIZE(a[0]); j++) {
			inputBox2d(box2d, &a[i][j], i);
		}
	}

	delBox2d1d(box2d, delIndex);
	size_t retSize = 0;
	size_t *retColSize = NULL;
	int **ret = (int **)expectBox2d(box2d, &retSize, &retColSize);

	if (retSize != keyRetSize) {
		printf("%s failed, retSize %ld should be %ld\n",
				__func__, retSize, keyRetSize);
		return;
	}
	for (size_t i = 0; i < retSize; i++) {
		int index = i >= delIndex ? i + 1 : i;

		if (retColSize[i] != ARRAYSIZE(a[index])) {
			printf("%s failed, retColSize %ld should be %ld\n",
					__func__, retColSize[i], ARRAYSIZE(a[index]));
			break;
		}
		for (size_t j = 0; j < retColSize[i]; j++) {
			if (a[index][j] != ret[i][j]) {
				printf("%s failed, ret[%ld][%ld] %d should be %d\n",
						__func__, i, j, ret[i][j], a[index][j]);
			}
		}
	}
	for (size_t i = 0; i < retSize; i++) {
		free(ret[i]);
	}
	free(ret);
	free(retColSize);
}

REGISTER_TEST_CASE(case_2);

int compareElment(const void *a, const void *b)
{
	return *(int*)a - *(int*)b;
}

int compare(const struct box **a, const struct box **b)
{
	return compareBox(*a, *b, compareElment);
}

void case_3(void)
{
	int a[][3] = {{4, 5, 6}, {1, 2, 3}};
	int key[][3] = {{1, 2, 3}, {4, 5, 6}};
	struct box2d *box2d = newBox2d(sizeof(int));
	size_t keyRetSize = 1;

	for (size_t i = 0; i < ARRAYSIZE(a); i++) {
		for (size_t j = 0; j < ARRAYSIZE(a[0]); j++) {
			inputBox2d(box2d, &a[i][j], i);
		}
	}

	sortBox2d(box2d, compare);

	size_t retSize = 0;
	size_t *retColSize = NULL;
	int **ret = (int **)expectBox2d(box2d, &retSize, &retColSize);

	if (retSize != ARRAYSIZE(key)) {
		printf("%s failed, retSize %ld should be %ld\n",
				__func__, retSize, ARRAYSIZE(key));
		return;
	}
	for (size_t i = 0; i < retSize; i++) {
		if (retColSize[i] != ARRAYSIZE(key[i])) {
			printf("%s failed, retColSize %ld should be %ld\n",
					__func__, retColSize[i], ARRAYSIZE(key[i]));
			break;
		}
		for (size_t j = 0; j < retColSize[i]; j++) {
			if (key[i][j] != ret[i][j]) {
				printf("%s failed, ret[%ld][%ld] %d should be %d\n",
						__func__, i, j, ret[i][j], key[i][j]);
			}
		}
	}
	for (size_t i = 0; i < retSize; i++) {
		free(ret[i]);
	}
	free(ret);
	free(retColSize);
}

REGISTER_TEST_CASE(case_3);

