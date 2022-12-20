#include "lcHead.h"

/* return the index of this function put */
/* There is a box manager struct in this version,
 *  more faster ! */
int putLeftOrRight(int sl, int position, int lThesisSum, int *returnSize, struct box *box) {
	/* finish the all rightThesis */
	if (sl - position == lThesisSum) {
		*returnSize = 1;
		char **stringPoint = inputBox(box, malloc(sizeof(char) * sl + 1));
		for (int i = position; i < sl; i++) {
			(*stringPoint)[i] = ')';
		}
		(*stringPoint)[sl] = '\0';
		return headBox(box) - 1;
	}

	/* put the leftThesis */
	int returnSizeL = 0;
	int indexL = putLeftOrRight(sl, position + 1, lThesisSum + 1, &returnSizeL, box);
	char **returnStringL = memoryBox(box, indexL);
	for (int i = 0; i < returnSizeL; i++) {
		(returnStringL[i])[position] = '(';
	}

	/* put the rightThesis */
	int returnSizeR = 0;

	if (lThesisSum > 0) {
		int indexR = putLeftOrRight(sl, position + 1, lThesisSum - 1, &returnSizeR, box);
		char **returnStringR = memoryBox(box, indexR);
		for (int i = 0; i < returnSizeR; i++) {
			(returnStringR[i])[position] = ')';
		}
	}

	*returnSize = returnSizeL + returnSizeR;
	return indexL;
}
char ** generateParenthesis(int n, int* returnSize){
	if (n < 1) {
		*returnSize = 0;
		return NULL;
	}
	struct box *box = newBox();

	putLeftOrRight(n*2, 0, 0, returnSize, box);


	char **ret;
	expectBox(box, &ret, returnSize);
	return ret;
}

void case_1(void)
{
	int retSize = 0;
	int testN = 1;
	char **ret = generateParenthesis(testN, &retSize);

	printf("\n++++++++++%d++++++++++\n", testN);
	for (int i = 0; i < retSize; i++) {
//		printf("%s\n", ret[i]);
		free(ret[i]);
	}
	free(ret);
	printf("retSize = %d\n", retSize);
}

void case_2(void)
{
	int retSize = 0;
	int testN = 3;
	char **ret = generateParenthesis(testN, &retSize);

	printf("\n++++++++++%d++++++++++\n", testN);
	for (int i = 0; i < retSize; i++) {
//		printf("%s\n", ret[i]);
		free(ret[i]);
	}
	free(ret);
	printf("retSize = %d\n", retSize);
}

void case_3(void)
{
	int retSize = 0;
	int testN = 8;
	char **ret = generateParenthesis(testN, &retSize);

	printf("++++++++++%d++++++++++\n", testN);
	for (int i = 0; i < retSize; i++) {
//		printf("%s\n", ret[i]);
		free(ret[i]);
	}
	free(ret);
	printf("retSize = %d\n", retSize);
}

REGISTER_TEST_CASE(case_1);
REGISTER_TEST_CASE(case_2);
REGISTER_TEST_CASE(case_3);

