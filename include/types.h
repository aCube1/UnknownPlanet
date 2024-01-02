#ifndef _TYPES_H_
#define _TYPES_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t s8;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64;

typedef size_t usize;

typedef struct Color {
	u8 r; /* Red (0 - 255) */
	u8 g; /* Green (0 - 255) */
	u8 b; /* Blue (0 - 255) */
	u8 a; /* Alpha (0 - 255) */
} Color;

#endif /* _TYPES_H_ */
