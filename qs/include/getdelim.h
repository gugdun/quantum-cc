#ifndef _GETDELIM_H
#define _GETDELIM_H

#include <limits.h>
#include <stdint.h>

ssize_t qcc_getdelim(char **restrict lineptr, size_t *restrict n, int delimiter,
    FILE *restrict stream);
ssize_t qcc_getline(char **restrict lineptr, size_t *restrict n,
   FILE *restrict stream);

#endif // _GETDELIM_H
