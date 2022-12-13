#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

char **putLeftOrRight(int sl, int position, int lThesisSum, int *returnSize) {
    /* finish the all rightThesis */
    if (sl - position == lThesisSum) {
        *returnSize = 1;
        char **ret = malloc(sizeof(char *) * 1);
        *ret = malloc(sizeof(char) * sl + 1);
        for (int i = position; i < sl; i++) {
            (*ret)[i] = ')';
        }
        (*ret)[sl] = '\0';
        return ret;
    }

    /* put the leftThesis */
    int returnSizeL = 0;
    char **returnStringL = putLeftOrRight(sl, position + 1, lThesisSum + 1, &returnSizeL);
    for (int i = 0; i < returnSizeL; i++) {
        (returnStringL[i])[position] = '(';
    }

    /* put the rightThesis */
    int returnSizeR = 0;
    char **returnStringR = NULL;
    if (lThesisSum > 0) {
        returnStringR = putLeftOrRight(sl, position + 1, lThesisSum - 1, &returnSizeR);
        for (int i = 0; i < returnSizeR; i++) {
            (returnStringR[i])[position] = ')';
        }
    }


    *returnSize = returnSizeL + returnSizeR;
    char **ret = malloc(sizeof(char *) * *returnSize);
    for (int i = 0; i < returnSizeR; i++) {
        ret[i] = returnStringR[i];
    }

    for (int i = 0; i < returnSizeL; i++) {
        ret[i + returnSizeR] = returnStringL[i];
    }

    free(returnStringL);
    free(returnStringR);
    return ret;
}
char ** generateParenthesis(int n, int* returnSize){
    if (n < 1) {
        *returnSize = 0;
        return NULL;
    }
    return putLeftOrRight(n*2, 0, 0, returnSize);
}


#define CASE_1
#ifdef CASE_1
int case_1(void)
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
	return 0;
}
#endif

#define CASE_2
#ifdef CASE_2
int case_2(void)
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
	return 0;
}
#endif

#define CASE_3
#ifdef CASE_3
int case_3(void)
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
	return 0;
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
	return 0;
}


