#include "lcHead.h"

int longestValidParentheses(char * s)
{
	ssize_t sl = strlen(s);
	ssize_t max = 0;
	ssize_t thisSringStart = 0;

	int rightParentheseNum = 0;

	for (int i = 0; i < sl; i++) {
		if (s[i] == '(') {
			rightParentheseNum++;
			continue;
		}

		if (rightParentheseNum > 0) {
			rightParentheseNum --;
			continue;
		}

		if (i - thisSringStart > max) {
			max = i - thisSringStart;
		}

		thisSringStart = i + 1;
	}

	/* this is mean maybe there is a longest valid parenthese at the last string */
	if (sl - thisSringStart - rightParentheseNum < max)
		return max;

	/* if whole the last string is valid, we return the string length */
	if (rightParentheseNum == 0)
		return sl - thisSringStart;

	/* we can sure the left parenthese must less than right parenthese */
	ssize_t thisStringEnd = sl;
	int leftParentheseNum = 0;

	for (int i = thisStringEnd; i >= (int)thisSringStart; i--) {
		if (s[i] == ')') {
			leftParentheseNum++;
			continue;
		}

		if (leftParentheseNum > 0) {
			leftParentheseNum --;
			continue;
		}
		
		if (thisStringEnd - (i + 1) > max) {
			max = thisStringEnd - (i + 1);
		}

		thisStringEnd = i;
	}

	if (leftParentheseNum == 0 && thisStringEnd - thisSringStart > max)
		return thisStringEnd - thisSringStart;

	return max;

}

void case_1(void)
{
	char *s = "";
	int keyRet = 0;

	int ret = longestValidParentheses(s);

	if (keyRet != ret)
		printf("%s is failed, ret %d should be %d\n",
				__func__, ret, keyRet);
}

void case_2(void)
{
	char *s = ")()())";
	int keyRet = 4;

	int ret = longestValidParentheses(s);

	if (keyRet != ret)
		printf("%s is failed, ret %d should be %d\n",
				__func__, ret, keyRet);
}

void case_3(void)
{
	char *s = "(()";
	int keyRet = 2;

	int ret = longestValidParentheses(s);

	if (keyRet != ret)
		printf("%s is failed, ret %d should be %d\n",
				__func__, ret, keyRet);
}

void case_4(void)
{
	char *s = "()(()";
	int keyRet = 2;

	int ret = longestValidParentheses(s);

	if (keyRet != ret)
		printf("%s is failed, ret %d should be %d\n",
				__func__, ret, keyRet);
}

void case_5(void)
{
	char *s = "()";
	int keyRet = 2;

	int ret = longestValidParentheses(s);

	if (keyRet != ret)
		printf("%s is failed, ret %d should be %d\n",
				__func__, ret, keyRet);
}

void case_6(void)
{
	char *s = "(())(";
	int keyRet = 4;

	int ret = longestValidParentheses(s);

	if (keyRet != ret)
		printf("%s is failed, ret %d should be %d\n",
				__func__, ret, keyRet);
}

REGISTER_TEST_CASE(case_1);
REGISTER_TEST_CASE(case_2);
REGISTER_TEST_CASE(case_3);
REGISTER_TEST_CASE(case_4);
REGISTER_TEST_CASE(case_5);
REGISTER_TEST_CASE(case_6);

