#include "lcHead.h"

#include <assert.h>

/* This is base function each student taught in school. */
#define LONG_MULTIPLICATION

/* TODO: This solution is so bad at performance, improve it */
#ifdef LONG_MULTIPLICATION
/* The input from leetcode is high to low, this is every uncomfortbale,
 * Since we always need to determine IS THERE A CARRY.
 * As first version, we can reverse the input, Don't think about the performance.
 */
static char *reverse(char *str)
{
	/* reverse the string mean exchange the value */
	int str_len = strlen(str);
	char *ret = malloc(str_len + 1);

	for (int i = str_len - 1; i >= 0; i--)
		ret[str_len - 1 - i] = str[i];

	ret[str_len] = '\0';

	return ret;
}

/* transfer one digit ascii to int */
#define a2i(x) (((x) - '0'))
/* transfer two digits ascii to int */
#define a2i2(x) ((((x) - '0') + ((&(x))[1] - '0') * 10))

char *multiply(char *num1, char *num2)
{
	char *num1_r = reverse(num1);
	char *num2_r = reverse(num2);

	int len_num1 = strlen(num1_r);
	int len_num2 = strlen(num2_r);

	/* 3 => two char for carray, one char for '0' */
	int len_ret = len_num1 + len_num2 + 3;
	char *ret_r = malloc(len_ret);
	memset(ret_r, '0', len_ret);

	for (int i = 0; i < len_num1; i++) {
		for (int j = 0; j < len_num2; j++) {
			int digit_mul = a2i(num1_r[i]) * a2i(num2_r[j]);
			/* since there is singal digit multiply,
			 * we will get less than 3 digits.
			 * we take two of ret_r string */
			digit_mul += a2i2(ret_r[i + j]);
			/* digit_mul have two situation now:
			 * 1.  xx (two digit)
			 * 2. 1xx (three digit, hightest is carray) */
			/* replace low two digits */
			ret_r[i + j] = digit_mul % 10 + '0';
			ret_r[i + j + 1] = (digit_mul / 10) % 10 + '0';
			/* add carray */
			ret_r[i + j + 2] += (digit_mul / 100);
		}
	}

	for (int i = len_ret - 1; i > 0; i--) {
		if (ret_r[i] != '0')
			break;
		ret_r[i] = '\0';
	}

	char *ret = reverse(ret_r);
	free(num1_r);
	free(num2_r);
	free(ret_r);
	return ret;
}
#endif

void case_1(void)
{
	char *num1 = "2";
	char *num2 = "3";
	char *key = "6";

	char *ret = multiply(num1, num2);

	if (strcmp(ret, key) != 0) {
		printf("Fail %s, should be %s\n", ret, key);
	}
	free(ret);
}
REGISTER_TEST_CASE(case_1);

void case_2(void)
{
	char *num1 = "123";
	char *num2 = "456";
	char *key = "56088";

	char *ret = multiply(num1, num2);

	if (strcmp(ret, key) != 0) {
		printf("Fail %s, should be %s\n", ret, key);
	}
	free(ret);
}
REGISTER_TEST_CASE(case_2);

void case_3(void)
{
	char *num1 = "123";
	char *key = "321";

	char *ret = reverse(num1);
	assert(strcmp(ret, key) == 0);
	free(ret);
}
REGISTER_TEST_CASE(case_3);

void case_4(void)
{
	char *num1 = "12345";
	int key = 43;

	int ret = a2i2(num1[2]);
	assert(ret == key);
}
REGISTER_TEST_CASE(case_4);

void case_5(void)
{
	char *num1 = "0";
	char *num2 = "0";
	char *key = "0";

	char *ret = multiply(num1, num2);
	assert(strcmp(ret, key) == 0);
	free(ret);
}
REGISTER_TEST_CASE(case_5);

