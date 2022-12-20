#ifndef __BITMAP__H_
#define __BITMAP__H_

#include <stdlib.h>
#include <string.h>

#define DIV_ROUND_UP(a, b) ((a + b - 1) / b)
typedef unsigned long long int bitmap_t;
#define __BITMAP_BITW__ (sizeof(bitmap_t) * 4)

struct bitmap {
	size_t elementCount;
	bitmap_t buffer[0];
};

static inline size_t sizeBitmap(struct bitmap *bitmap)
{
	return DIV_ROUND_UP(bitmap->elementCount, __BITMAP_BITW__) * sizeof(bitmap->buffer[0]);
}

static inline void setAllBitmap(struct bitmap *bitmap, bool v)
{
	memset(bitmap->buffer, v?0xff:0, sizeBitmap(bitmap));
}

static inline struct bitmap *newBitmap(size_t elementCount)
{
	struct bitmap *bitmap = malloc(sizeof(struct bitmap)
			+ DIV_ROUND_UP(elementCount, __BITMAP_BITW__) * sizeof(bitmap->buffer[0]));

	if (!bitmap)
		return bitmap;

	bitmap->elementCount = elementCount;
	return bitmap;
}

static inline void setBitmap(struct bitmap *bitmap, size_t index)
{
	if (index > bitmap->elementCount)
		return;

	bitmap->buffer[index/__BITMAP_BITW__] |= 1 << (index%__BITMAP_BITW__);
}

static inline bool getBitmap(struct bitmap *bitmap, size_t index)
{
	if (index > bitmap->elementCount)
		return false;

	return bitmap->buffer[index/__BITMAP_BITW__] & 1 << (index%__BITMAP_BITW__);
}

static inline size_t ffsBitmap(struct bitmap *bitmap)
{
	int i = 0;
	for (i = 0; i < DIV_ROUND_UP(bitmap->elementCount, __BITMAP_BITW__); i++) {
		if (bitmap->buffer[i])
			break;
	}

	if (i == DIV_ROUND_UP(bitmap->elementCount, __BITMAP_BITW__))
		return -1;

	return i * __BITMAP_BITW__ + ffs(bitmap->buffer[i]) - 1;
}

static inline void clearBitmap(struct bitmap *bitmap, size_t index)
{
	if (index > bitmap->elementCount)
		return;
	bitmap->buffer[index/__BITMAP_BITW__] &= ~(1 << (index%__BITMAP_BITW__));
}

#endif

