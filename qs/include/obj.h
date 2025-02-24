#ifndef _OBJ_H
#define _OBJ_H

#include <stdint.h>

typedef struct {
    uint16_t addr;
    uint8_t name_size;
    char *name;
} tag_t;

typedef struct {
    uint16_t addr;
    uint8_t name_size;
    char *name;
} link_t;

typedef struct {
    uint16_t tag_count;
    uint16_t link_count;
    uint16_t alloc_size;
    uint16_t size;
    tag_t *tags;
    link_t *links;
    uint8_t *data;
} object_t;

#endif // _OBJ_H

