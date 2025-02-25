#ifndef _GETDELIM_H
#define _GETDELIM_H

#include <limits.h>

#ifndef _POSIX_SOURCE
typedef long ssize_t;
#define SSIZE_MAX LONG_MAX
#endif

ssize_t qcc_getdelim(char **restrict lineptr, size_t *restrict n, int delimiter,
    FILE *restrict stream);
ssize_t qcc_getline(char **restrict lineptr, size_t *restrict n,
   FILE *restrict stream);

#endif // _GETDELIM_H
