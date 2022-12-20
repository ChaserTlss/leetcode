#ifndef __LCBOX_H__
#define __LCBOX_H__
/* this box manager a char * array. */
struct box {
	size_t boxSize;
	size_t boxHead;
	char **boxMemory;
};

static inline struct box *newBox(void)
{
	struct box *ret = malloc(sizeof(struct box));
	ret->boxSize = 32;
	ret->boxHead = 0;
	ret->boxMemory = malloc(sizeof(char *) * ret->boxSize);

	return ret;
}

/* remember to free(*table) */
static inline void expectBox(struct box *box, char ***table, int *retSize)
{
	*table = box->boxMemory;
	*retSize = box->boxHead;
	free(box);
}

static inline char **inputBox(struct box *box, char *string)
{
	if (box->boxHead + 1 >= box->boxSize) {
		box->boxMemory = realloc(box->boxMemory, box->boxSize * 2 * sizeof(char*));
		box->boxSize *= 2;
	}

	box->boxMemory[box->boxHead] = string;
	return &box->boxMemory[box->boxHead++];
}

static inline int headBox(struct box *box)
{
	return box->boxHead;
}

static inline char **memoryBox(struct box *box, int index)
{
	return &box->boxMemory[index];
}

#endif
