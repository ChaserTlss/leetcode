#include "lcHead.h"
#define CPUBTMEM

#ifndef CPUBTMEM
bool isValidSudoKu(char board[][9], int boardSize, int *boardColSize) {
	struct bitmap *bitmap = newBitmap(10);
	bool ret = true;

	/* check row */
	for (int i = 0; i < boardSize; i++) {
		setAllBitmap(bitmap, 0);
		for (int j = 0; j < boardSize; j++) {
			if (board[i][j] == '.')
				continue;
			size_t index = board[i][j] - '0';
			if (getBitmap(bitmap, index)) {
				ret = false;
				goto OUT;
			}
			setBitmap(bitmap, index);
		}
	}

	/* check col */
	for (int i = 0; i < boardSize; i++) {
		setAllBitmap(bitmap, 0);
		for (int j = 0; j < boardSize; j++) {
			if (board[j][i] == '.')
				continue;
			size_t index = board[j][i] - '0';
			if (getBitmap(bitmap, index)) {
				ret = false;
				goto OUT;
			}
			setBitmap(bitmap, index);
		}
	}

	/* check group */
	for (int i = 0; i < boardSize; i++) {
		setAllBitmap(bitmap, 0);
		for (int j = 0; j < boardSize; j++) {
			int row = j % 3 + (i % 3) * 3;
			int col = j / 3 + (i / 3) * 3;
			if (board[col][row] == '.')
				continue;
			size_t index = board[col][row] - '0';
			if (getBitmap(bitmap, index)) {
				ret = false;
				goto OUT;
			}
			setBitmap(bitmap, index);
		}
	}

OUT:
	free(bitmap);
	return ret;
}
#else
bool isValidSudoKu(char board[][9], int boardSize, int *boardColSize) {
	struct bitmap *bitmap[13];
	bool ret = true;
	for (int i = 0; i < 13; i++) {
		bitmap[i] = newBitmap(10);
		setAllBitmap(bitmap[i], 0);
	}

	/* check row */
	for (int i = 0; i < boardSize; i++) {
		setAllBitmap(bitmap[0], 0);
		if (i % 3 == 0) {
			setAllBitmap(bitmap[1], 0);
			setAllBitmap(bitmap[2], 0);
			setAllBitmap(bitmap[3], 0);
		}

		for (int j = 0; j < boardSize; j++) {
			if (board[i][j] == '.')
				continue;
			size_t index = board[i][j] - '0';

			/* check row */
			if (getBitmap(bitmap[0], index)) {
				ret = false;
				goto OUT;
			}
			setBitmap(bitmap[0], index);

			/* check group */
			int bitGroup = 1 + j / 3;
			if (getBitmap(bitmap[bitGroup], index)) {
				ret = false;
				goto OUT;
			}
			setBitmap(bitmap[bitGroup], index);

			/* check col */
			if (getBitmap(bitmap[4 + j], index)) {
				ret = false;
				goto OUT;
			}
			setBitmap(bitmap[4 + j], index);
		}
	}

OUT:
	for (int i = 0; i < 13; i++) {
		free(bitmap[i]);
	}
	return ret;
}
#endif
void case_1(void)
{
	char a[9][9] = {
		{'5','3','.','.','7','.','.','.','.'},
		{'6','.','.','1','9','5','.','.','.'},
		{'.','9','8','.','.','.','.','6','.'},
		{'8','.','.','.','6','.','.','.','3'},
		{'4','.','.','8','.','3','.','.','1'},
		{'7','.','.','.','2','.','.','.','6'},
		{'.','6','.','.','.','.','2','8','.'},
		{'.','.','.','4','1','9','.','.','5'},
		{'.','.','.','.','8','.','.','7','9'}};
	bool keyRet = true;

	bool ret = isValidSudoKu(a, ARRAYSIZE(a), NULL);

	if (ret != keyRet) {
		printf("%s failed, ret %d should be %d\n",
				__func__, ret, keyRet);
	}
}

void case_2(void)
{
	char a[][9] = {
		{'8','3','.','.','7','.','.','.','.'},
		{'6','.','.','1','9','5','.','.','.'},
		{'.','9','8','.','.','.','.','6','.'},
		{'8','.','.','.','6','.','.','.','3'},
		{'4','.','.','8','.','3','.','.','1'},
		{'7','.','.','.','2','.','.','.','6'},
		{'.','6','.','.','.','.','2','8','.'},
		{'.','.','.','4','1','9','.','.','5'},
		{'.','.','.','.','8','.','.','7','9'}};
	bool keyRet = false;

	bool ret = isValidSudoKu(a, ARRAYSIZE(a), NULL);

	if (ret != keyRet) {
		printf("%s failed, ret %d should be %d\n",
				__func__, ret, keyRet);
	}
}

REGISTER_TEST_CASE(case_1);
REGISTER_TEST_CASE(case_2);

