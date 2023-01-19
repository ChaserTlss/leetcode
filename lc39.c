#include "lcHead.h"
/* question:
Given an array of distinct integers candidates and a target integer target, return a list of all unique combinations of candidates where the chosen numbers sum to target. You may return the combinations in any order.

The same number may be chosen from candidates an unlimited number of times. Two combinations are unique if the 
frequency
 of at least one of the chosen numbers is different.

The test cases are generated such that the number of unique combinations that sum up to target is less than 150 combinations for the given input.

Constraints:

1 <= candidates.length <= 30
2 <= candidates[i] <= 40
All elements of candidates are distinct.
1 <= target <= 40
*/

/********** code **********/
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int **combinationSum(int *candidates, int candidatesSize, int target, int *returnSize, int **returnColumnSizes)
{
	return NULL;
}

/********** test **********/
void case_1(void)
{
	int candidates[] = {2, 3, 6, 7};
	int target = 7;
	int keyReturn[][20] = {{2, 2, 3}, {7}};

	int returnSize = 0;
	int *returnColumnSizes;
	int **ret = combinationSum(candidates, ARRAYSIZE(candidates), target, &returnSize, &returnColumnSizes);

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
	}
}
REGISTER_TEST_CASE(case_1);
