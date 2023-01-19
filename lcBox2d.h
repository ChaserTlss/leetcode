#ifndef __LCBOX2D_H__
#define __LCBOX2D_H__

#include "lcBox.h"

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
#endif
