#include "lcHead.h"

int divide(int dividend, int divisor)
{
	unsigned int i = 0;
	unsigned int __dividend = dividend;
	unsigned int __divisor = divisor;
	int sign = 1;

	if (divisor == 0)
		return 0;

	if (dividend < 0) {
		__dividend = ~(__dividend) + 1;
		sign = -sign;
	}
	if (divisor < 0) {
		__divisor = ~(__divisor) + 1;
		sign = - sign;
	}

	while (__dividend >= __divisor) {
		__dividend -= __divisor;
		i++;
	}
	if (i > INT_MAX && sign > 0)
		return INT_MAX;

	return sign > 0 ? i : -i;
}

void case_1(void)
{
	int dividend = INT_MIN;
	int divisor = -1;

	int ret = divide(dividend, divisor);
	int check = INT_MAX;

	if (ret != check ) {
		printf("%s failed, ret %d should be %d\n", __func__, ret, check);
	}
}

void case_2(void)
{
	int dividend = 10;
	int divisor = 3;

	int ret = divide(dividend, divisor);
	int check = dividend/ divisor;

	if (ret != check ) {
		printf("%s failed, ret %d should be %d\n", __func__, ret, check);
	}
}

void case_3(void)
{
	int dividend = 7;
	int divisor = -3;

	int ret = divide(dividend, divisor);
	int check = dividend/ divisor;

	if (ret != check ) {
		printf("%s failed, ret %d should be %d\n", __func__, ret, check);
	}
}

void case_4(void)
{
	int dividend = 7;
	int divisor = 1;

	int ret = divide(dividend, divisor);
	int check = dividend/ divisor;

	if (ret != check ) {
		printf("%s failed, ret %d should be %d\n", __func__, ret, check);
	}
}

void case_5(void)
{
	int dividend = INT_MIN;
	int divisor = 1;

	int ret = divide(dividend, divisor);
	int check = dividend/ divisor;

	if (ret != check ) {
		printf("%s failed, ret %d should be %d\n", __func__, ret, check);
	}
}

void case_6(void)
{
	int dividend = 2147483647;
	int divisor = 2;

	int ret = divide(dividend, divisor);
	int check = dividend/ divisor;

	if (ret != check ) {
		printf("%s failed, ret %d should be %d\n", __func__, ret, check);
	}
}

REGISTER_TEST_CASE(case_1);
REGISTER_TEST_CASE(case_2);
REGISTER_TEST_CASE(case_3);
REGISTER_TEST_CASE(case_4);
REGISTER_TEST_CASE(case_5);
REGISTER_TEST_CASE(case_6);

