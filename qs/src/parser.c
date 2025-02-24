#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <parser.h>

#define LINE_ALLOC_SIZE 32
#define DATA_CHUNK_SIZE 256

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

void add_tag(char *name, uint16_t addr, object_t *obj)
{
    if (!obj->tags) obj->tags = (tag_t *)malloc(sizeof(tag_t));
    else obj->tags = (tag_t *)realloc(obj->tags, sizeof(tag_t) * (obj->tag_count + 1));
    tag_t *last_tag = &obj->tags[obj->tag_count - 1];
    last_tag->addr = addr;
    last_tag->name_size = (uint8_t)strlen(name);
    last_tag->name = (char *)malloc(last_tag->name_size);
    strcpy(last_tag->name, (const char*)name);
    ++obj->tag_count;
}

void add_link(char *name, uint16_t addr, object_t *obj)
{
    if (!obj->links) obj->links = (link_t *)malloc(sizeof(link_t));
    else obj->links = (link_t *)realloc(obj->links, sizeof(link_t) * (obj->link_count + 1));
    link_t *last_link = &obj->links[obj->link_count - 1];
    last_link->addr = addr;
    last_link->name_size = (uint8_t)strlen(name);
    last_link->name = (char *)malloc(last_link->name_size);
    strcpy(last_link->name, (const char*)name);
    ++obj->link_count;
}

void add_data(uint8_t *chunk, uint16_t size, object_t *obj)
{
    if (!obj->data)
    {
        obj->data = (uint8_t *)malloc(DATA_CHUNK_SIZE);
        obj->alloc_size = DATA_CHUNK_SIZE;
        obj->size = 0;
    }
    else if (obj->size + size > obj->alloc_size)
    {
        obj->data = (uint8_t *)realloc(obj->data, obj->alloc_size + DATA_CHUNK_SIZE);
        obj->alloc_size += DATA_CHUNK_SIZE;
    }
    memcpy((void *)&obj->data[obj->size], (void *)chunk, (size_t)size);
    obj->size += size;
}

int parse_line(int number, char *line, object_t *obj)
{
    printf("%5d | %s", number, line);
    return 0;
}

int parse_file(char *path, object_t *obj)
{
    FILE *file = fopen(path, "r");
    if (!file)
    {
        printf("File not found: %s\n", path);
        return 1;
    }

    ssize_t read = 0;
    int exit_code = 0;
    int number = 1;
    size_t len = LINE_ALLOC_SIZE;
    char *line = (char *)malloc(LINE_ALLOC_SIZE);
    
    while ((read = getline(&line, &len, file)) != -1)
    {
        if (parse_line(number, line, obj))
        {
            exit_code = 1;
            break;
        }
        ++number;
    }

    free(line);
    fclose(file);
    
    return exit_code;
}

