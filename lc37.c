#include "lcHead.h"

struct boardState {
	struct bitmap *vertical[9];
	struct bitmap *horizontal[9];
	struct bitmap *group[9];
};

#define VH2GROUP(ver, hor) (hor/3 + ver/3*3)
void updateBoardState(struct boardState *bs, size_t ver, size_t hor, char val)
{
	if (val < '1' || val > '9')
		return;
	clearBitmap(bs->horizontal[hor], val - '1');
	clearBitmap(bs->vertical[ver], val - '1');
	clearBitmap(bs->group[VH2GROUP(ver, hor)], val - '1');
}

#define ONLYBIT(t) (t && !(t & ~(1 << (ffs(t) - 1))))
int solveBoardState(struct boardState *bs, size_t ver, size_t hor)
{
	size_t group = VH2GROUP(ver, hor);
	bitmap_t t =  bs->horizontal[hor]->buffer[0]
		& bs->vertical[ver]->buffer[0]
		& bs->group[group]->buffer[0]
		& 0x1FF;

	if (ONLYBIT(t)) {
		return ffs(t);
	}

	bitmap_t other_ver = 0;
	for (int i = 0; i < 9; i++) {
		if (i != ver) {
			other_ver |= bs->vertical[i]->buffer[0];
		}
	}

	bitmap_t p = t ^ other_ver & t;
	if (ONLYBIT(p)) {
		return ffs(p);
	}

	bitmap_t other_group = 0;
	for (int i = 0; i < 9; i++) {
		if (VH2GROUP(i, hor) == group && i != ver) {
			other_group |= bs->vertical[i]->buffer[0];
		}
		if (VH2GROUP(ver, i) == group && i != hor) {
			other_group |= bs->horizontal[i]->buffer[0];
		}
	}
	
	p = t ^ other_group & t;
	if (ONLYBIT(p)) {
		return ffs(p);
	}

	bitmap_t other_hor = 0;
	for(int i = 0; i < 9; i++) {
		if (i != hor) {
			other_hor |= bs->horizontal[i]->buffer[0];
		}
	}
	p = t ^ other_hor & t;
	if (ONLYBIT(p)) {
		return ffs(p);
	}
	return 0;
}

/* *ret: 0 is end */
void allSolution(struct boardState *bs, size_t ver, size_t hor, int *ret)
{
	size_t group = VH2GROUP(ver, hor);
	bitmap_t t =  bs->horizontal[hor]->buffer[0]
		& bs->vertical[ver]->buffer[0]
		& bs->group[group]->buffer[0]
		& 0x1FF;

	int head = 0;
	while (t) {
		ret[head++] = ffs(t);
		t &= ~(1 << (ffs(t) - 1));
	}
}
#ifdef CHECKPOINT_1
bitmap_t checkpoint_1[9][3];
#endif
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
			if (board[i][j] == '.') {
				ret = false;
				goto OUT;
			}
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

void solveSudoku(char board[][9], int boardSize, int* boardColSize);
bool __solveSudoku(char board[][9], int boardSize)
{
	solveSudoku(board, boardSize, &boardSize);
	return isValidSudoKu(board, boardSize, &boardSize);
}

void deepCopy(char board[][9], char back[9][9])
{
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			back[i][j] = board[i][j];
		}
	}
}

void backup(char board[][9], char back[9][9])
{
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			board[i][j] = back[i][j];
		}
	}
}

void solveSudoku(char board[][9], int boardSize, int* boardColSize)
{
	struct boardState bs;
	for (int i = 0; i < ARRAYSIZE(bs.vertical); i++) {
		bs.vertical[i] = newBitmap(10);
		bs.horizontal[i] = newBitmap(10);
		bs.group[i] = newBitmap(10);
		setAllBitmap(bs.vertical[i], 1);
		setAllBitmap(bs.horizontal[i], 1);
		setAllBitmap(bs.group[i], 1);
	}

	/* load the board */
	/* loop board */
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			/* update boardState */
			updateBoardState(&bs, i, j, board[i][j]);
		}
	}

#ifdef CHECKPOINT_1
	for (int i = 0; i < ARRAYSIZE(bs.vertical); i++) {
		if (bs.vertical[i]->buffer[0] != checkpoint_1[i][0]) {
			printf("checkpoint_0 failed, bs.vertical[%d] is 0x%x, should 0x%x\n",
					i, bs.vertical[i]->buffer[0], checkpoint_1[i][0]);
		}
		if (bs.horizontal[i]->buffer[0] != checkpoint_1[i][1]) {
			printf("checkpoint_0 failed, bs.horizontal[%d] is 0x%x, should 0x%x\n",
					i, bs.vertical[i]->buffer[0], checkpoint_1[i][1]);
		}
		if (bs.group[i]->buffer[0] != checkpoint_1[i][2]) {
			printf("checkpoint_0 failed, bs.group[%d] is 0x%x, should 0x%x\n",
					i, bs.group[i]->buffer[0], checkpoint_1[i][2]);
		}
	}
#endif


	/* loop: still unresloved unit */
LOOP:
	/* find only one result unit */
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			if (board[i][j] != '.')
				continue;
			int bt = solveBoardState(&bs, i, j);
			if (bt) {
				board[i][j] = bt + '0';
				updateBoardState(&bs, i, j, board[i][j]);
				goto LOOP;
			}
		}
	}

	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			if (board[i][j] == '.') {
				int all[9] = {0};
				allSolution(&bs, i, j, all);
				char tempBoard[9][9];
				deepCopy(board, tempBoard);
				int head = 0;
				while (all[head]) {
					board[i][j] = all[head++] + '0';
					if (__solveSudoku(board, boardSize))
						goto OUT;
					backup(board, tempBoard);
				}
				printf("solve failed %d %d\n", i, j);
				goto OUT;
			}
		}
	}

OUT:
	for (int i = 0; i < ARRAYSIZE(bs.vertical); i++) {
		free(bs.vertical[i]);
		free(bs.horizontal[i]);
		free(bs.group[i]);
	}

}

void printBoard(char board[9][9], const char keyBoard[9][9])
{
	for (int i = 0; i < 9; i++) {
		if (i % 3 == 0)
			printf("---------------------------------------\n");
		for (int j = 0; j < 9; j++) {
			if (j % 3 == 0)
				printf("|");
			if (board[i][j] == keyBoard[i][j])
				printf(" %c  ", board[i][j]);
			else
				printf(" %c/%c", board[i][j], keyBoard[i][j]);
		}
		printf("\n");
	}
}

void case_1(void)
{
	char board[][9] = {
		{'5','3','.','.','7','.','.','.','.'},
		{'6','.','.','1','9','5','.','.','.'},
		{'.','9','8','.','.','.','.','6','.'},
		{'8','.','.','.','6','.','.','.','3'},
		{'4','.','.','8','.','3','.','.','1'},
		{'7','.','.','.','2','.','.','.','6'},
		{'.','6','.','.','.','.','2','8','.'},
		{'.','.','.','4','1','9','.','.','5'},
		{'.','.','.','.','8','.','.','7','9'},};
	const char keyRet[][9] = {
		{'5','3','4','6','7','8','9','1','2'},
		{'6','7','2','1','9','5','3','4','8'},
		{'1','9','8','3','4','2','5','6','7'},
		{'8','5','9','7','6','1','4','2','3'},
		{'4','2','6','8','5','3','7','9','1'},
		{'7','1','3','9','2','4','8','5','6'},
		{'9','6','1','5','3','7','2','8','4'},
		{'2','8','7','4','1','9','6','3','5'},
		{'3','4','5','2','8','6','1','7','9'},};

#ifdef CHECKPOINT_1
	checkpoint_1[0][0] = ~(1 << 4 | 1 << 2 | 1 << 6);
	checkpoint_1[1][0] = ~(1 << 5 | 1 << 0 | 1 << 8 | 1 << 4);
	checkpoint_1[2][0] = ~(1 << 8 | 1 << 7 | 1 << 5);
	checkpoint_1[3][0] = ~(1 << 7 | 1 << 5 | 1 << 2);
	checkpoint_1[4][0] = ~(1 << 3 | 1 << 7 | 1 << 2 | 1 << 0);
	checkpoint_1[5][0] = ~(1 << 6 | 1 << 1 | 1 << 5);
	checkpoint_1[6][0] = ~(1 << 5 | 1 << 1 | 1 << 7);
	checkpoint_1[7][0] = ~(1 << 3 | 1 << 0 | 1 << 8 | 1 << 4);
	checkpoint_1[8][0] = ~(1 << 7 | 1 << 6 | 1 << 8);

	checkpoint_1[0][1] = ~(1 << 4 | 1 << 5 | 1 << 7 | 1 << 3 | 1 << 6);
	checkpoint_1[1][1] = ~(1 << 2 | 1 << 8 | 1 << 5);
	checkpoint_1[2][1] = ~(1 << 7);;
	checkpoint_1[3][1] = ~(1 << 0 | 1 << 7 | 1 << 3);
	checkpoint_1[4][1] = ~(1 << 6 | 1 << 8 | 1 << 5 | 1 << 1 | 1 << 0 | 1 << 7);
	checkpoint_1[5][1] = ~(1 << 4 | 1 << 2 | 1 << 8);
	checkpoint_1[6][1] = ~(1 << 1);
	checkpoint_1[7][1] = ~(1 << 5 | 1 << 7 | 1 << 6);
	checkpoint_1[8][1] = ~(1 << 2 | 1 << 0 | 1 << 5 | 1 << 4 | 1 << 8);

	checkpoint_1[0][2] = ~(1 << 4 | 1 << 2 | 1 << 5 | 1 << 8 | 1 << 7);
	checkpoint_1[1][2] = ~(1 << 6 | 1 << 0 | 1 << 8 | 1 << 4);
	checkpoint_1[2][2] = ~(1 << 5);;
	checkpoint_1[3][2] = ~(1 << 7 | 1 << 3 | 1 << 6);
	checkpoint_1[4][2] = ~(1 << 5 | 1 << 7 | 1 << 2 | 1 << 1);
	checkpoint_1[5][2] = ~(1 << 2 | 1 << 0 | 1 << 5);
	checkpoint_1[6][2] = ~(1 << 5);
	checkpoint_1[7][2] = ~(1 << 3 | 1 << 0 | 1 << 8 | 1 << 7);
	checkpoint_1[8][2] = ~(1 << 1 | 1 << 7 | 1 << 4 | 1 << 6 | 1 << 8);
#endif

	solveSudoku(board, ARRAYSIZE(board), NULL);

	for (int i = 0; i < ARRAYSIZE(board); i++) {
		for (int j = 0; j < ARRAYSIZE(board[0]); j++) {
			if (board[i][j] != keyRet[i][j]) {
				printf("%s failed\n", __func__);
				printBoard(board, keyRet);
				return;
			}
		}
	}

}

void case_2(void)
{
	char board[][9] = {
		{'.','.','9','7','4','8','.','.','.'},
		{'7','.','.','.','.','.','.','.','.'},
		{'.','2','.','1','.','9','.','.','.'},
		{'.','.','7','.','.','.','2','4','.'},
		{'.','6','4','.','1','.','5','9','.'},
		{'.','9','8','.','.','.','3','.','.'},
		{'.','.','.','8','.','3','.','2','.'},
		{'.','.','.','.','.','.','.','.','6'},
		{'.','.','.','2','7','5','9','.','.'},};
	const char keyRet[][9] = {
		{'5','1','9','7','4','8','6','3','2'},
		{'7','8','3','6','5','2','4','1','9'},
		{'4','2','6','1','3','9','8','7','5'},
		{'3','5','7','9','8','6','2','4','1'},
		{'2','6','4','3','1','7','5','9','8'},
		{'1','9','8','5','2','4','3','6','7'},
		{'9','7','5','8','6','3','1','2','4'},
		{'8','3','2','4','9','1','7','5','6'},
		{'6','4','1','2','7','5','9','8','3'}, };

	solveSudoku(board, ARRAYSIZE(board), NULL);

	for (int i = 0; i < ARRAYSIZE(board); i++) {
		for (int j = 0; j < ARRAYSIZE(board[0]); j++) {
			if (board[i][j] != keyRet[i][j]) {
				printf("%s failed\n", __func__);
				printBoard(board, keyRet);
				return;
			}
		}
	}
}

REGISTER_TEST_CASE(case_1);
REGISTER_TEST_CASE(case_2);

