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

REGISTER_TEST_CASE(case_1);
REGISTER_TEST_CASE(case_2);
REGISTER_TEST_CASE(case_3);

