#ifndef __LCBOX2D_H__
#define __LCBOX2D_H__

#include "lcBox.h"
#include <assert.h>

struct box2d {
	struct box *box;
	size_t box2dElementSize;
};

static inline struct box2d *
newBox2d(size_t elementSize)
{
	struct box2d *ret = malloc(sizeof(struct box2d));
	ret->box2dElementSize = elementSize;
	ret->box = newBox(sizeof(struct box *));

	return ret;
}

static inline void *
inputBox2d(struct box2d *box2d, void *element, size_t index1d)
{
	while (headBox(box2d->box) <= index1d) {
		struct box *box = newBox(box2d->box2dElementSize);
		inputBox(box2d->box, &box);
	}

	return inputBox(*(struct box **)memoryBox(box2d->box, index1d), element);
}

static inline void *
inputBox2d1d(struct box2d *box2d, const struct box *box)
{
	struct box *tbox = newBox(box2d->box2dElementSize);
	void *ret = inputBox(box2d->box, &tbox);
	cpyBox(tbox, box);
	return ret;
}

static inline void *
memoryBox2d(struct box2d *box2d, int index1d, int index2d)
{
	return memoryBox(memoryBox(box2d->box, index1d), index2d);
}

static inline size_t
headBox2d(struct box2d *box2d)
{
	return headBox(box2d->box);
}

static inline size_t
headBox2d1d(struct box2d *box2d, int index1d)
{
	return headBox(memoryBox(box2d->box, index1d));
}

static inline void *
expectBox2d(struct box2d *box2d, size_t *retSize, size_t **retColSize)
{
	struct box *retColArray = newBox(sizeof(size_t));
	struct box **table = NULL;
	expectBox(box2d->box, (void **)&table, retSize);
	for (int i = 0; i < *retSize; i++) {
		struct box *box = table[i];
		size_t retSizet = 0;
		expectBox(box, (void **)&table[i], &retSizet);
		inputBox(retColArray, &retSizet);
	}
	expectBox(retColArray, (void **)retColSize, retSize);
	free(box2d);
	return (void *)table;
}

static inline void
delBox2d(struct box2d *box2d, int index1d, int index2d)
{
	return delBox(memoryBox(box2d->box, index1d), index2d);
}

/* Pls user to confirm to clean all element in this box2d[index1d] */
static inline void
delBox2d1d(struct box2d *box2d, int index1d)
{
	struct box *box = *((struct box **)memoryBox(box2d->box, index1d));
	free(box->boxMemory);
	free(box);
	delBox(box2d->box, index1d);
}

typedef int (*compareBox2d)(const struct box **boxa, const struct box **boxb);

#ifdef NESTED_FUNCTION
static inline void
sortBox2d(struct box2d *box2d, compareBoxElement compare)
{
	int __compare(const struct box **boxa, const struct box **boxb) {
		return compareBox(*boxa, *boxb, compare);
	}
	return sortBox(box2d->box, (compareBoxElement)__compare);
}
#else
static inline void
sortBox2d(struct box2d *box2d, compareBoxElement compare)
{
	assert(0);
}
#endif

static inline void
destoryBox2d(struct box2d *box2d)
{
	for (int i = 0; i < headBox2d(box2d); i++) {
		destoryBox(*(struct box **)memoryBox(box2d->box, i));
	}
	destoryBox(box2d->box);
	free(box2d);
}

static inline bool
checkBox2d1d(struct box2d *box2d, struct box *box, compareBoxElement compare) {
	for (int i = 0; i < headBox2d(box2d); i++) {
		struct box *boxElement = *(struct box **)memoryBox(box2d->box, i);
		if (compareBox(boxElement, box, compare) == 0) {
			return true;
		}
	}
	return false;
}

#endif

