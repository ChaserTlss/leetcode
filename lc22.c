#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* this box manager a char * array. */
struct box {
	size_t boxSize;
	size_t boxHead;
	char **boxMemory;
};

struct box *newBox(void)
{
	struct box *ret = malloc(sizeof(struct box));
	ret->boxSize = 32;
	ret->boxHead = 0;
	ret->boxMemory = malloc(sizeof(char *) * ret->boxSize);

	return ret;
}

/* remember to free(*table) */
void expectBox(struct box *box, char ***table, int *retSize)
{
	*table = box->boxMemory;
	*retSize = box->boxHead;
	free(box);
}

char **inputBox(struct box *box, char *string)
{
	if (box->boxHead + 1 >= box->boxSize) {
		box->boxMemory = realloc(box->boxMemory, box->boxSize * 2 * sizeof(char*));
		box->boxSize *= 2;
	}

	box->boxMemory[box->boxHead] = string;
	return &box->boxMemory[box->boxHead++];
}

int headBox(struct box *box)
{
	return box->boxHead;
}

char **memoryBox(struct box *box, int index)
{
	return &box->boxMemory[index];
}

/* return the index of this function put */
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


