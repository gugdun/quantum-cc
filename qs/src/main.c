#include <stdio.h>
#include <stdint.h>
#include <config.h>

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
    uint16_t size;
    uint16_t name_size;
    uint16_t tag_count;
    uint16_t link_count;
    char *name;
    tag_t *tags;
    link_t *links;
    uint8_t *data;
} section_t;

typedef struct {
    uint8_t section_count;
    section_t *sections;
} object_t;

int main(int argc, char *argv[])
{
    printf(
        "qs version %d.%d.%d by %s\n",
        VERSION_MAJOR,
        VERSION_MINOR,
        VERSION_PATCH,
        DEVELOPER
    );
    return 0;
}

