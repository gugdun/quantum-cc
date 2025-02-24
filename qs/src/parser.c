#include <stdio.h>
#include <stdlib.h>
#include <parser.h>

#define LINE_ALLOC_SIZE 32

size_t getline(char **lineptr, size_t *n, FILE *stream) {
    char *bufptr = NULL;
    char *p = bufptr;
    size_t size;
    int c;

    if (lineptr == NULL) {
        return -1;
    }
    if (stream == NULL) {
        return -1;
    }
    if (n == NULL) {
        return -1;
    }
    bufptr = *lineptr;
    size = *n;

    c = fgetc(stream);
    if (c == EOF) {
        return -1;
    }
    if (bufptr == NULL) {
        bufptr = malloc(128);
        if (bufptr == NULL) {
            return -1;
        }
        size = 128;
    }
    p = bufptr;
    while(c != EOF) {
        if (((size_t)p - (size_t)bufptr) > (size - 1)) {
            size = size + 128;
            bufptr = realloc(bufptr, size);
            if (bufptr == NULL) {
                return -1;
            }
        }
        *p++ = c;
        if (c == '\n') {
            break;
        }
        c = fgetc(stream);
    }

    *p++ = '\0';
    *lineptr = bufptr;
    *n = size;

    return p - bufptr - 1;
}

int parse_line(int number, char *line)
{
    printf("%5d | %s", number, line);
    return 0;
}

int parse_file(char *path, object_t *obj)
{
    int code = 0;

    FILE *file = fopen(path, "r");
    if (!file)
    {
        printf("File not found: %s\n", path);
        return 1;
    }

    ssize_t read;
    int number = 1;
    size_t len = LINE_ALLOC_SIZE;
    char *line = (char *)malloc(LINE_ALLOC_SIZE);
    while ((read = getline(&line, &len, file)) != -1)
    {
        if (parse_line(number, line))
        {
            code = 1;
            break;
        }
        ++number;
    }

    free(line);
    fclose(file);
    
    return code;
}

