#include "common.h"

#include "log.h"

#include <stdlib.h>

void *xcalloc(usize count, usize size) {
	void *ptr = calloc(count, size);
	if (ptr == NULL && size != 0) {
		log_fatal("calloc() failed: %zu, %zu", count, size);
		exit(EXIT_FAILURE);
	}

	return ptr;
}

void *xrealloc(void *ptr, usize size) {
	void *tmp = realloc(ptr, size);
	if (tmp == NULL && size != 0) {
		log_fatal("realloc() failed: %zu", size);
		exit(EXIT_FAILURE);
	}

	return tmp;
}

FILE *xfopen(const char *filename, const char *mode) {
	FILE *file = fopen(filename, mode);
	if (file == NULL) {
		log_fatal("fopen() failed: %s, %s", filename, mode);
		exit(EXIT_FAILURE);
	}

	return file;
}

FILE *xfreopen(const char *filename, const char *mode, FILE *stream) {
	FILE *file = freopen(filename, mode, stream);
	if (file == NULL) {
		log_fatal("freopen() failed: %s, %s", filename, mode);
		exit(EXIT_FAILURE);
	}

	return file;
}
