#ifndef _CORE_TIME_H_
#define _CORE_TIME_H_

#include "types.h"

typedef struct Time {
	double current;
	double previous;
	double update; /* Delta time for frame update */
	double render; /* Delta time for frame render */
	double frame;  /* Delta time for one frame */
} Time;

s32 time_getfps(const Time *time);

void wait_time(double seconds);
double get_time(void);

#endif /* _CORE_TIME_H_ */
