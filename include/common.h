#ifndef _COMMON_H_
#define _COMMON_H_

#include "types.h"

#include <stdio.h>

double get_time(void);

void *xcalloc(usize count, usize size);
void *xrealloc(void *ptr, usize size);

FILE *xfopen(const char *filename, const char *mode);
FILE *xfreopen(const char *filename, const char *mode, FILE *stream);

#endif /* _COMMON_H_ */
