#ifndef __LCBOX_H__
#define __LCBOX_H__

#include <stdlib.h>
#include <string.h>

#ifndef __BOX_START_ELEMENT_SIZE__ 
#define __BOX_START_ELEMENT_SIZE__ 64
#endif

#ifndef __BOX_REALLOC_SIZE__ 
#define __BOX_REALLOC_SIZE__ 2
#endif
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

static inline void *memoryBox(struct box *box, int index)
{
	return box->boxMemory + index * box->boxElementSize;
}

/* keey one zero element at finally position */
static inline void *inputBox(struct box *box, void *element)
{
	if (box->boxHead + 1 >= box->boxElementMax) {
		box->boxMemory = realloc(box->boxMemory,
				box->boxElementMax * __BOX_REALLOC_SIZE__ * box->boxElementSize);
		box->boxElementMax *= __BOX_REALLOC_SIZE__;
	}

	size_t position = box->boxHead * box->boxElementSize;

	memcpy(memoryBox(box, box->boxHead), element, box->boxElementSize);
	box->boxHead += 1;
	memset(memoryBox(box, box->boxHead), 0, box->boxElementSize);
	return box->boxMemory + position;
}

static inline size_t headBox(struct box *box)
{
	return box->boxHead;
}

static inline void delBox(struct box *box, int index)
{
/*=================================================================
==2339==ERROR: AddressSanitizer: memcpy-param-overlap: memory ranges [0x611000000408,0x611000000411) and [0x61100000040c, 0x611000000415) overlap
    #0 0x7f8e7f16b1ed in __interceptor_memcpy ../../../../src/libsanitizer/sanitizer_common/sanitizer_common_interceptors.inc:827
    #1 0x556d6778e4af in delBox /home/daimiao/leetcode/lcBox.h:72
    #2 0x556d6779142a in case_4 /home/daimiao/leetcode/lcBox.c:149
    #3 0x556d6778ed2f in main /home/daimiao/leetcode/lcHead.h:63
    #4 0x7f8e7e8fdd8f in __libc_start_call_main ../sysdeps/nptl/libc_start_call_main.h:58
    #5 0x7f8e7e8fde3f in __libc_start_main_impl ../csu/libc-start.c:392
    #6 0x556d6778d364 in _start (/home/daimiao/leetcode/a.out+0x7364)
    */
	memmove(memoryBox(box, index), memoryBox(box, index + 1),
			(box->boxHead-- - index - 1) * box->boxElementSize);
}

static inline void cpyBox(struct box *dbox, const struct box *sbox)
{
	dbox->boxHead = sbox->boxHead;
	dbox->boxElementMax = sbox->boxElementMax;
	dbox->boxElementSize = sbox->boxElementSize;
	memcpy(dbox->boxMemory, sbox->boxMemory, dbox->boxElementSize * dbox->boxHead);

}

static inline void destoryBox(struct box *box)
{
	free(box->boxMemory);
	free(box);
}

#endif
