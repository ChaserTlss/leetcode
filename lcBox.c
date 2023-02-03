#include "lcHead.h"

void case_1(void)
{
	int a[] = {1, 2};
	size_t test_size = test_size;

	struct box *box = newBox(sizeof(a[0]));

	for (size_t i = 0; i < test_size; i++) {
		size_t head = headBox(box);
		if (head != i) {
			printf("%s is failed, headBox return wrong %ld, should be %ld\n",
					__func__, head, i);
		}

		void *t = inputBox(box, &a[i]);
		if (t != box->boxMemory + i * sizeof(a[0])) {
			printf("%s is failed, inputBox return wrong %p, should be %p\n",
					__func__, t, box->boxMemory + i);
		}
	}

	for (int i = 0; i < test_size; i++) {
		void *t = memoryBox(box, i);
		if (*(int *)t != a[i]) {
			printf("%s is failed, memoryBox return wrong %d, should be %d\n",
					__func__, *(int *)t, a[i]);
		}
	}

	void *t;
	size_t size;
	expectBox(box, &t, &size);
	for (int i = 0; i < size; i++) {
		if (((int *)t)[i] != a[i]) {
			printf("%s is failed, expectBox give wrong table element %d, should be %d\n",
					__func__, ((int *)t)[i], a[i]);
		}
	}

	free(t);

}

/* element more than __BOX_START_ELEMENT_SIZE__ */
void case_2(void)
{
	size_t test_size = __BOX_START_ELEMENT_SIZE__ * 2 - 1;
	int *a = malloc(sizeof(*a) * test_size);

	for (size_t i = 0; i < test_size; i++) {
		a[i] = rand();
	}
	struct box *box = newBox(sizeof(a[0]));

	for (size_t i = 0; i < test_size; i++) {
		size_t head = headBox(box);
		if (head != i) {
			printf("%s is failed, headBox return wrong %ld, should be %ld\n",
					__func__, head, i);
		}

		void *t = inputBox(box, &a[i]);
		if (t != box->boxMemory + i * sizeof(a[0])) {
			printf("%s is failed, inputBox return wrong %p, should be %p\n",
					__func__, t, box->boxMemory + i);
		}
	}

	for (int i = 0; i < test_size; i++) {
		void *t = memoryBox(box, i);
		if (*(int *)t != a[i]) {
			printf("%s is failed, memoryBox return wrong %d, should be %d\n",
					__func__, *(int *)t, a[i]);
		}
	}

	void *t;
	size_t size;
	expectBox(box, &t, &size);
	for (int i = 0; i < size; i++) {
		if (((int *)t)[i] != a[i]) {
			printf("%s is failed, expectBox give wrong table element %d, should be %d\n",
					__func__, ((int *)t)[i], a[i]);
		}
	}

	free(t);
	free(a);
}
/* element more than __BOX_START_ELEMENT_SIZE__*2 */
void case_3(void)
{
	size_t test_size = __BOX_START_ELEMENT_SIZE__ * 3 - 1;
	int *a = malloc(sizeof(*a) * test_size);

	for (size_t i = 0; i < test_size; i++) {
		a[i] = rand();
	}
	struct box *box = newBox(sizeof(a[0]));

	for (size_t i = 0; i < test_size; i++) {
		size_t head = headBox(box);
		if (head != i) {
			printf("%s is failed, headBox return wrong %ld, should be %ld\n",
					__func__, head, i);
		}

		void *t = inputBox(box, &a[i]);
		if (t != box->boxMemory + i * sizeof(a[0])) {
			printf("%s is failed, inputBox return wrong %p, should be %p\n",
					__func__, t, box->boxMemory + i);
		}
	}

	for (int i = 0; i < test_size; i++) {
		void *t = memoryBox(box, i);
		if (*(int *)t != a[i]) {
			printf("%s is failed, memoryBox return wrong %d, should be %d\n",
					__func__, *(int *)t, a[i]);
		}
	}

	void *t;
	size_t size;
	expectBox(box, &t, &size);
	for (int i = 0; i < size; i++) {
		if (((int *)t)[i] != a[i]) {
			printf("%s is failed, expectBox give wrong table element %d, should be %d\n",
					__func__, ((int *)t)[i], a[i]);
		}
	}

	free(t);
	free(a);
}

void case_4(void)
{
	int a[] = {1, 2, 3, 4, 5, 6};
	struct box *box = newBox(sizeof(int));
	int delIndex = 2;

	for (size_t i = 0; i < ARRAYSIZE(a); i++) {
		inputBox(box, &a[i]);
	}

	delBox(box, delIndex);
	size_t retSize = 0;
	int *ret = NULL;
	expectBox(box, (void **)&ret, &retSize);

	for (size_t i = 0; i < retSize; i++) {
		size_t index = i >= delIndex ? i + 1 : i;
		if (i >= ARRAYSIZE(a) - 1) {
			printf("%s failed, retSize %ld is too large, should be %ld\n",
					__func__, retSize, ARRAYSIZE(a));
			break;
		}
		if (ret[i] != a[index]) {
			printf("%s failed, ret[%ld] %d should be %d\n",
					__func__, i, ret[i], a[index]);
			break;
		}
	}
	free(ret);
}

int compare(const void *a, const void *b)
{
	return *(int *)a - *(int *)b;
}

void case_5(void)
{
	int a[] = {3, 2, 1, 6, 5, 4};
	int key[] = {1, 2, 3, 4, 5, 6};
	struct box *box = newBox(sizeof(int));

	for (size_t i = 0; i < ARRAYSIZE(a); i++) {
		inputBox(box, &a[i]);
	}

	sortBox(box, compare);
	size_t retSize = 0;
	int *ret = NULL;
	expectBox(box, (void **)&ret, &retSize);

	for (size_t i = 0; i < retSize; i++) {
		if (i >= ARRAYSIZE(key)) {
			printf("%s failed, retSize %ld is too large, should be %ld\n",
					__func__, retSize, ARRAYSIZE(key));
			break;
		}
		if (ret[i] != key[i]) {
			printf("%s failed, ret[%ld] %d should be %d\n",
					__func__, i, ret[i], key[i]);
			break;
		}
	}
	free(ret);
}

void case_6(void)
{
	struct box *box = newBox(sizeof(int));
	struct box *dbox = newBox(sizeof(int));

	/* make memory realloc */
	for (int i = 0; i < 2 * __BOX_START_ELEMENT_SIZE__; i++) {
		inputBox(box, &i);
	}

	cpyBox(dbox, box);

	for (int i = 0; i < 2 * __BOX_START_ELEMENT_SIZE__; i++) {
		if (*(int *)memoryBox(dbox, i) != i)
			printf("%s is failed! dbox[i] is %d, should be %d\n",
					__func__, *(int *)memoryBox(dbox, i), i);
	}

	destoryBox(box);
	destoryBox(dbox);
}


REGISTER_TEST_CASE(case_1);
REGISTER_TEST_CASE(case_2);
REGISTER_TEST_CASE(case_3);
REGISTER_TEST_CASE(case_4);
REGISTER_TEST_CASE(case_5);
REGISTER_TEST_CASE(case_6);

