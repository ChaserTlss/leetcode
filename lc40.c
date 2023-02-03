#include "lcHead.h"
/********** code **********/
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int compareInt(const void *a, const void *b)
{
	return *(int *)a - *(int *)b;
}

void combinationSumHelper(int *candidates, int candidatesSize, int target, struct box2d *box2d, struct box *box, struct box2d *alreadyCheckTable)
{
	for (int i = 0; i < candidatesSize; i++) {
		inputBox(box, &candidates[i]);
		for (int i = 0; i < headBox2d(alreadyCheckTable); i++) {
			if (compareBox(*(struct box **)memoryBox(alreadyCheckTable->box, i), box, compareInt) == 0) {
				goto OUTLOOP;
			}
		}
		inputBox2d1d(alreadyCheckTable, box);

		if (candidates[i] == target) {
			inputBox2d1d(box2d, box);

		} else if (candidates[i] < target) {

			combinationSumHelper(candidates + i + 1, candidatesSize - i - 1, target - candidates[i], box2d, box, alreadyCheckTable);
		}
OUTLOOP:
		delBox(box, headBox(box) - 1);
		if (candidates[i] > target) {
			break;
		}
	}
}

int **combinationSum2(int *candidates, int candidatesSize, int target, int *returnSize, int **returnColumnSizes)
{
	struct box2d *box2d = newBox2d(sizeof(int));
	struct box2d *alreadyCheckTable = newBox2d(sizeof(int));
	struct box *box = newBox(sizeof(int));

	qsort(candidates, candidatesSize, sizeof(int), compareInt);
	combinationSumHelper(candidates, candidatesSize, target, box2d, box, alreadyCheckTable);

	size_t retSize = 0;
	size_t *retColSize = NULL;
	int **ret = expectBox2d(box2d, &retSize, &retColSize);
	*returnColumnSizes = malloc(sizeof(int) * retSize);
	for (int i = 0; i < retSize; i++) {
		(*returnColumnSizes)[i] = retColSize[i];
	}
	*returnSize = retSize;


	free(retColSize);
	destoryBox(box);
	destoryBox2d(alreadyCheckTable);
	return ret;
}

/********** test **********/
void case_1(void)
{
	int candidates[] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
	int target = 30;
	int keyReturn[][31] = {{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,}};

	int returnSize = 0;
	int *returnColumnSizes;
	int **ret = combinationSum2(candidates, ARRAYSIZE(candidates), target, &returnSize, &returnColumnSizes);

	if (returnSize != ARRAYSIZE(keyReturn))
			printf("%s failed, returnSize %d is wrong, should be %ld\n",
					__func__, returnSize, ARRAYSIZE(keyReturn));
	for (int i = 0; i < returnSize; i++) {
		if (i >= ARRAYSIZE(keyReturn)) {
			printf("%s failed, returnSize %d is too large, should be %ld\n",
					__func__, returnSize, ARRAYSIZE(keyReturn));
			printf("ret[%d] :", i);
			for (int j = 0; j < returnColumnSizes[i]; j++) {
				printf(" %d,", ret[i][j]);
			}
			printf("\n");
		} else if (returnColumnSizes[i] >= ARRAYSIZE(keyReturn[i])) {
			printf("%s failed, returnColumnSize[%d] %d is too large, should be %ld\n",
					__func__, i, returnColumnSizes[i], ARRAYSIZE(keyReturn[i]));
			printf("ret[%d] :", i);
			for (int j = 0; j < returnColumnSizes[i]; j++) {
				printf(" %d,", ret[i][j]);
			}
			printf("\n");
		} else {
			for (int j = 0; j < returnColumnSizes[i]; j++) {
				if (ret[i][j] != keyReturn[i][j]) {
					printf("%s failed, ret[%d][%d] %d should be %d\n",
							__func__, i, j, ret[i][j], keyReturn[i][j]);
				}
			}
		}
		free(ret[i]);
	}
	free(returnColumnSizes);
	free(ret);
}
REGISTER_TEST_CASE(case_1);
