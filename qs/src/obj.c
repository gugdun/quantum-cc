#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <obj.h>

#define DATA_CHUNK_SIZE 256

void add_tag(char *name, uint16_t addr, object_t *obj)
{
    if (!obj->tags) obj->tags = (tag_t *)malloc(sizeof(tag_t));
    else obj->tags = (tag_t *)realloc(obj->tags, sizeof(tag_t) * (obj->tag_count + 1));
    tag_t *last_tag = &obj->tags[obj->tag_count];
    last_tag->addr = addr;
    last_tag->name_size = (uint8_t)strlen(name);
    last_tag->name = (char *)malloc(last_tag->name_size + 1);
    strcpy(last_tag->name, (const char*)name);
    ++obj->tag_count;
#ifdef DEBUG
    printf("FNCALL| add_tag(%s, 0x%04X)\n", last_tag->name, last_tag->addr);
#endif
}

void add_link(char *name, uint16_t addr, object_t *obj)
{
    if (!obj->links) obj->links = (link_t *)malloc(sizeof(link_t));
    else obj->links = (link_t *)realloc(obj->links, sizeof(link_t) * (obj->link_count + 1));
    link_t *last_link = &obj->links[obj->link_count];
    last_link->addr = addr;
    last_link->name_size = (uint8_t)strlen(name);
    last_link->name = (char *)malloc(last_link->name_size + 1);
    strcpy(last_link->name, (const char*)name);
    ++obj->link_count;
#ifdef DEBUG
    printf("FNCALL| add_link(%s, 0x%04X)\n", last_link->name, last_link->addr);
#endif
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
#ifdef DEBUG
    printf("FNCALL| add_data(0x%04X)\n", size);
#endif
}
