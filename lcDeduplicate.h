#ifndef __LCDEDUPLICATE_H__
#define __LCDEDUPLICATE_H__
#include <stdlib.h>

/* return the int array that keep number the which items repeat times */
/* base should have been sorted */
static inline int *deduplicate(void *base, size_t nitems, size_t size, int (*compare)(const void *, const void *), int *returnSize)
{
	if (!nitems) {
		*returnSize = 0;
		return NULL;
	}

	size_t checkKey;
	size_t check;
	size_t fill;

	int *hash = malloc(sizeof(int) * nitems);
	memset(hash, 0, sizeof(int) * nitems);

	checkKey = 0;
	check = fill = 1;

	while (check != nitems) {
		if (compare(base + check * size, base + checkKey * size)) {
			memcpy(base + fill * size, base + check * size, size);
			checkKey = fill;
			fill++;
		} else {
			hash[checkKey] += 1;
		}

		check++;
	}
	
	*returnSize = fill;
	return hash;
}

#endif

