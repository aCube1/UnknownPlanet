#ifndef _CONFIG_H_
#define _CONFIG_H_

#if defined(WIN32) || defined(_WIN32)
#	define OS_WINDOWS 1
#endif

#if defined(linux) || defined(__linux) || defined(__linux__)
#	define OS_UNIX 1
#endif

#if defined(__FreeBSD__) || defined(__OpenBSD__)
#	define OS_UNIX 1
#endif

/* Check if we are on a unsupported platform */
#if !defined(OS_WINDOW) && !defined(OS_UNIX)
#	error Unable to detect target platform
#endif

#endif /* _CONFIG_H_ */
