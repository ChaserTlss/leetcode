#ifndef __LCFINDPOSTIONBS_H__
#define __LCFINDPOSTIONBS_H__
#include <stdlib.h>

static size_t findPostionBS(const void *key, const void *base, size_t nitems, size_t size, int (*compar)(const void *, const void *), size_t bias)
{
	int p = nitems / 2;

	if (p == 0) {
		if (nitems == 0 || compar(base, key) > 0)
			return bias;
		else
			return bias + 1;
	}

	int pVsKey = compar(base + size * p, key);

	if (pVsKey > 0 && compar(base + size * (p - 1), key) <= 0)
		return p + bias;

	if (pVsKey > 0)
		return findPostionBS(key, base, nitems - p - 1, size, compar, bias);
	else
		return findPostionBS(key, base + size * (p + 1), nitems - p - 1, size, compar, bias + p + 1);
}

static inline size_t findP(const void *key, const void *base, size_t nitems, size_t size, int (*compar)(const void *, const void *))
{
	if (nitems == 0)
		return 0;
	return findPostionBS(key, base, nitems, size, compar, 0);
}

#endif

