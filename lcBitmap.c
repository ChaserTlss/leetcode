#include "lcHead.h"

void case_1(void)
{
	struct bitmap *bitmap = newBitmap(10);

	setAllBitmap(bitmap, 0);
	size_t index = ffsBitmap(bitmap);
	if (index != -1) {
		printf("%s failed, index %ld should be %d\n",
				__func__, index, -1);
	}

	setAllBitmap(bitmap, 1);
	index = ffsBitmap(bitmap);
	if (index != 0) {
		printf("%s failed, index %ld should be %d\n",
				__func__, index, 0);
	}

	setAllBitmap(bitmap, 0);
	setBitmap(bitmap, 1);
	bool b = getBitmap(bitmap, 1);
	if (b != true) {
		printf("%s failed, index 1 is %d, shoulbe be true\n",
				__func__, b);
	}
	b = getBitmap(bitmap, 9);
	if (b != false) {
		printf("%s failed, index 1 is %d, shoulbe be false\n",
				__func__, b);
	}

	free(bitmap);
}

void case_2(void)
{
	struct bitmap *bitmap = newBitmap(10);

	setAllBitmap(bitmap, 0);
	setBitmap(bitmap, 0);

	size_t index = ffsBitmap(bitmap);
	if (index != 0) {
		printf("%s failed, index %ld should be 0\n",
				__func__, index);
	}
	free(bitmap);
}

void case_3(void)
{
	struct bitmap *bitmap = newBitmap(10);

	setAllBitmap(bitmap, 1);

	bool r = getBitmap(bitmap, 3);
	if (r != true) {
		printf("%s failed, index 3 should be true\n", __func__);
	}

	r = getBitmap(bitmap, 1);
	if (r != true) {
		printf("%s failed, index 3 should be true\n", __func__);
	}

	size_t index = ffsBitmap(bitmap);
	if (index != 0) {
		printf("%s failed, index %ld should be 0\n",
				__func__, index);
	}
	free(bitmap);
}

void case_4(void)
{
	struct bitmap *bitmap = newBitmap(2);

	setAllBitmap(bitmap, 1);

	clearBitmap(bitmap, 0);
	clearBitmap(bitmap, 1);

	size_t index = ffsBitmap(bitmap);
	if (index != -1) {
		printf("%s failed, index %ld should be -1\n",
				__func__, index);
	}
	free(bitmap);
}

void case_5(void)
{
	struct bitmap *bitmap = newBitmap(120);

	setAllBitmap(bitmap, 1);

	clearBitmap(bitmap, 6);
	bool r = getBitmap(bitmap, 6);
	if (r != false) {
		printf("%s failed, index 6 should be false\n", __func__);
	}

	clearBitmap(bitmap, 32);
	r = getBitmap(bitmap, 32);
	if (r != false) {
		printf("%s failed, index 49 should be false\n", __func__);
	}

	if (bitmap->buffer[1] != ~(1 << 0)) {
		printf("%s failed, buffer[1] 0x%x should be 0x%x\n",
				__func__, bitmap->buffer[1], ~(1u<<0));
	}

	free(bitmap);
}

REGISTER_TEST_CASE(case_1);
REGISTER_TEST_CASE(case_2);
REGISTER_TEST_CASE(case_3);
REGISTER_TEST_CASE(case_4);
REGISTER_TEST_CASE(case_5);

