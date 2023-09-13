#include "lcHead.h"

void case_1(void)
{
}

void case_2(void)
{
}

REGISTER_TEST_CASE(case_1);
REGISTER_TEST_CASE(case_2);

void case_3(void)
{
	assert(((&case_2_fn) - (&case_1_fn)) == 1);
}

REGISTER_TEST_CASE(case_3);

