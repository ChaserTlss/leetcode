#include "lcHead.h"

void case_1(void)
{
	/* -1 is end */
	int a[][6] = {  {1, 2, 3, 4, 5, -1},
			{4, 5, 6, 7, -1},
			{1, -1},
			{3, 4, 5, 6, -1},
	};
	struct box2d *box2d = newBox2d(sizeof(int));

	for (int i = 0; i < ARRAYSIZE(a); i++) {
		for (int j = 0; j < ARRAYSIZE(a[0]);j++) {
			if (a[i][j] == -1)
				break;
			int  *ret = inputBox2d(box2d, &a[i][j], i);
			if (*ret != a[i][j])
				printf("%s is failed, inputBox2d return %p value %d, value should be %d\n",
						__func__, ret, *ret, a[i][j]);
			
		}
	}
	size_t size = 0;
	size_t *colSize = NULL;
	int **ret = NULL;

	ret = expectBox2d(box2d, &size, &colSize);
	if (size != ARRAYSIZE(a)) {
		printf("%s is failed, size %d should be %d\n",
				__func__, size, ARRAYSIZE(a));
	}

	for (int i = 0; i < size; i++) {
		if (colSize[i] > ARRAYSIZE(a[0])) {
			printf("%s is failed, colsize[%d] %d is larger than %d\n",
					__func__, i, colSize[i], ARRAYSIZE(a[0]));
			continue;
		}
		for (int j = 0; j < colSize[i]; j++) {
			if (a[i][j] == -1) {
				printf("%s is failed, colsize[%d] %d is bigger than real size\n");
				break;
			}
			if (a[i][j] != ret[i][j]) {
				printf("%s is failed, table[%d][%d] is %d should be %d\n",
						__func__, i, j, ret[i][j], a[i][j]);
			}
		}
		free(ret[i]);
	}
	free(ret);
	free(colSize);
}
REGISTER_TEST_CASE(case_1);

