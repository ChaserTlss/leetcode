#include "lcHead.h"

static inline int __fls(unsigned int v)
{
	int ret = 32;

	if (!v) return 0;

	if (!(v & 0xFFFF0000)) { v <<= 16; ret -= 16; }
	if (!(v & 0xFF000000)) { v <<= 8;  ret -= 8;  }
	if (!(v & 0xF0000000)) { v <<= 4;  ret -= 4;  }
	if (!(v & 0xC0000000)) { v <<= 2;  ret -= 2;  }
	if (!(v & 0x80000000)) { v <<= 1;  ret -= 1;  }

	return ret;
}

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

	int leftShiftBit = 32 - __fls(__divisor);

	while (__dividend >= __divisor) {
		while (__divisor << leftShiftBit > __dividend && leftShiftBit > 0)
			leftShiftBit -= 1;
		__dividend -= __divisor << leftShiftBit;
		i += 1ul << leftShiftBit;
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

void case_7(void)
{
	int v = 0b1000;
	int bitPostion = 4;

	if (bitPostion != __fls(v)) {
		printf("%s failed, ret %d should be %d\n", __func__, __fls(v), bitPostion);
	}

	v = 0;
	bitPostion = 0;
	if (bitPostion != __fls(v)) {
		printf("%s failed, ret %d should be %d\n", __func__, __fls(v), bitPostion);
	}

	v = 1;
	bitPostion = 1;
	if (bitPostion != __fls(v)) {
		printf("%s failed, ret %d should be %d\n", __func__, __fls(v), bitPostion);
	}

	v = 3;
	bitPostion = 2;
	if (bitPostion != __fls(v)) {
		printf("%s failed, ret %d should be %d\n", __func__, __fls(v), bitPostion);
	}
}

void case_8(void)
{
	int dividend = -2147483648;
	int divisor = -3;

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
REGISTER_TEST_CASE(case_7);
REGISTER_TEST_CASE(case_8);

