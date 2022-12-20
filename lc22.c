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

#define isLeft(a) (a == '(' || a == '[' || a == '{')
#define isRight(a) (a == ')' || a == ']' || a == '}')

bool isValid(char * s){
	int sl = strlen(s);
	char *stack = malloc(sl);
	int head = 0;

	for (int i = 0; i < sl; i++) {
		if (isLeft(s[i])) {
			stack[head++] = s[i];
		} else if (isRight(s[i])) {
			bool valid = 0;
			if (!head)
				goto FAILED;
			switch (stack[--head]) {
				case '(' :
					valid = s[i]  == ')';
					break;
				case '[' :
					valid = s[i]  == ']';
					break;
				case '{' :
					valid = s[i]  == '}';
					break;
				default:
					/* we will not in here */
					break;
			}
			if (!valid)
				goto FAILED;
		}
	}
	free(stack);
	return head == 0;
FAILED:
	free(stack);
	return false;
}

void case_1(void)
{
	int retSize = 0;
	int testN = 1;
	int keyRetSize = 1;
	char **ret = generateParenthesis(testN, &retSize);

	for (int i = 0; i < retSize; i++) {
		if (!isValid(ret[i])) {
			printf("%s failed, ret[%d]: %s\n",
					__func__, i, ret[i]);
		}
		free(ret[i]);
	}

	if (retSize != keyRetSize) {
		printf("%s failed, size %d should be %d\n",
				__func__, retSize, keyRetSize);
	}
	free(ret);
}

void case_2(void)
{
	int retSize = 0;
	int testN = 3;
	int keyRetSize = 5;
	char **ret = generateParenthesis(testN, &retSize);

	for (int i = 0; i < retSize; i++) {
		if (!isValid(ret[i])) {
			printf("%s failed, ret[%d]: %s\n",
					__func__, i, ret[i]);
		}
		free(ret[i]);
	}

	if (retSize != keyRetSize) {
		printf("%s failed, size %d should be %d\n",
				__func__, retSize, keyRetSize);
	}
	free(ret);
}

void case_3(void)
{
	int retSize = 0;
	int testN = 8;
	int keyRetSize = 1430;
	char **ret = generateParenthesis(testN, &retSize);

	for (int i = 0; i < retSize; i++) {
		if (!isValid(ret[i])) {
			printf("%s failed, ret[%d]: %s\n",
					__func__, i, ret[i]);
		}
		free(ret[i]);
	}

	if (retSize != keyRetSize) {
		printf("%s failed, size %d should be %d\n",
				__func__, retSize, keyRetSize);
	}
	free(ret);
}

REGISTER_TEST_CASE(case_1);
REGISTER_TEST_CASE(case_2);
REGISTER_TEST_CASE(case_3);

