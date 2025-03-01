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

void add_tag(char *name, uint16_t addr, object_t *obj);
void add_link(char *name, uint16_t addr, object_t *obj);
void add_data(uint8_t *chunk, uint16_t size, object_t *obj);

#endif // _OBJ_H

