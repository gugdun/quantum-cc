/* Implementations of the getdelim() and getline() functions from POSIX 2008,
   just in case your libc doesn't have them.
   getdelim() reads from a stream until a specified delimiter is encountered.
   getline() reads from a stream until a newline is encountered.
   See: http://pubs.opengroup.org/onlinepubs/9699919799/functions/getdelim.html
   NOTE: It is always the caller's responsibility to free the line buffer, even
   when an error occurs.
   Copyright (c) 2011 James E. Ingram
   Permission is hereby granted, free of charge, to any person obtaining a copy
   of this software and associated documentation files (the "Software"), to deal
   in the Software without restriction, including without limitation the rights
   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
   copies of the Software, and to permit persons to whom the Software is
   furnished to do so, subject to the following conditions:
   The above copyright notice and this permission notice shall be included in
   all copies or substantial portions of the Software.
   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
   THE SOFTWARE.
*/


#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <getdelim.h>


#if __STDC_VERSION__ >= 199901L
/* restrict is a keyword */
#else
# define restrict
#endif


#define _GETDELIM_GROWBY 128    /* amount to grow line buffer by */
#define _GETDELIM_MINLEN 4      /* minimum line buffer size */


ssize_t qcc_getdelim(char **restrict lineptr, size_t *restrict n, int delimiter,
                 FILE *restrict stream)
{
	char *buf, *pos;
	int c;
	ssize_t bytes;

	if (lineptr == NULL || n == NULL) {
		errno = EINVAL;
		return -1;
	}
	if (stream == NULL) {
		errno = EBADF;
		return -1;
	}

	/* resize (or allocate) the line buffer if necessary */
	buf = *lineptr;
	if (buf == NULL || *n < _GETDELIM_MINLEN) {
		buf = realloc(*lineptr, _GETDELIM_GROWBY);
		if (buf == NULL) {
			/* ENOMEM */
			return -1;
		}
		*n = _GETDELIM_GROWBY;
		*lineptr = buf;
	}

	/* read characters until delimiter is found, end of file is reached, or an
	   error occurs. */
	bytes = 0;
	pos = buf;
	while ((c = getc(stream)) != EOF) {
		if (bytes + 1 >= SSIZE_MAX) {
			errno = EOVERFLOW;
			return -1;
		}
		bytes++;
		if (bytes >= (ssize_t)(*n - 1)) {
			buf = realloc(*lineptr, *n + _GETDELIM_GROWBY);
			if (buf == NULL) {
				/* ENOMEM */
				return -1;
			}
			*n += _GETDELIM_GROWBY;
			pos = buf + bytes - 1;
			*lineptr = buf;
		}

		*pos++ = (char) c;
		if (c == delimiter) {
			break;
		}
	}

	if (ferror(stream) || (feof(stream) && (bytes == 0))) {
		/* EOF, or an error from getc(). */
		return -1;
	}

	*pos = '\0';
	return bytes;
}


ssize_t qcc_getline(char **restrict lineptr, size_t *restrict n,
                FILE *restrict stream)
{
	return qcc_getdelim(lineptr, n, '\n', stream);
}
