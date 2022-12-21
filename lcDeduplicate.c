#include "lcHead.h"

int compareInt(const void *item, const void *key)
{
	return *(int *)item - *(int *)key;
}

void case_1(void)
{
	int a[] = {1, 1, 2, 2, 3};
	int key[] = {1, 2, 3};
	int repeatMapKey[] = {1, 1, 0};

	int retSize;
	int *ret = deduplicate(a, ARRAYSIZE(a), sizeof(a[0]), compareInt, &retSize);

	int checkSize = retSize;
	if (retSize != ARRAYSIZE(repeatMapKey)) {
		printf("%s failed, retSize %d should be %ld\n",
				__func__, retSize, ARRAYSIZE(repeatMapKey));
		checkSize = retSize > ARRAYSIZE(repeatMapKey) ? ARRAYSIZE(repeatMapKey) : retSize;
	}

	for (int i = 0; i < checkSize; i++) {
		if (repeatMapKey[i] != ret[i]) {
			printf("%s failed, ret[%d] %d should be %d\n",
					__func__, i, ret[i], repeatMapKey[i]);
		}
	}

	for (int i = 0; i < checkSize; i++) {
		if (a[i] != key[i]) {
			printf("%s failed, a[%d] %d should be %d\n",
					__func__, i, a[i], key[i]);
		}
	}

	free(ret);
}

REGISTER_TEST_CASE(case_1);

