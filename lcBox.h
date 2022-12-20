#ifndef __LCBOX_H__
#define __LCBOX_H__
#define __BOX_START_ELEMENT_SIZE__ 32
#define __BOX_REALLOC_SIZE__ 2
/* this box manager a char * array. */
struct box {
	size_t boxHead;
	size_t boxElementMax;
	size_t boxElementSize;
	void *boxMemory;
};

static inline struct box *newBox(size_t elementSize)
{
	struct box *ret = malloc(sizeof(struct box));
	ret->boxElementMax = __BOX_START_ELEMENT_SIZE__;
	ret->boxElementSize = elementSize;
	ret->boxHead = 0;
	ret->boxMemory = malloc(elementSize * ret->boxElementMax);

	return ret;
}

/* remember to free(*table) */
static inline void expectBox(struct box *box, void **table, size_t *retSize)
{
	*table = box->boxMemory;
	*retSize = box->boxHead;
	free(box);
}

static inline void *inputBox(struct box *box, void *element)
{
	if (box->boxHead + 1 >= box->boxElementMax) {
		box->boxMemory = realloc(box->boxMemory,
				box->boxElementMax * __BOX_REALLOC_SIZE__ * box->boxElementSize);
		box->boxElementMax *= __BOX_REALLOC_SIZE__;
	}

	size_t position = box->boxHead * box->boxElementSize;

	memcpy(box->boxMemory + position, element, box->boxElementSize);
	box->boxHead += 1;
	return box->boxMemory + position;
}

static inline size_t headBox(struct box *box)
{
	return box->boxHead;
}

static inline void *memoryBox(struct box *box, int index)
{
	return box->boxMemory + index * box->boxElementSize;
}

#endif
