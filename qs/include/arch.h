#ifndef _ARCH_H
#define _ARCH_H

#include <stdint.h>
#include <stdbool.h>

typedef enum {
    REG = 1,
    ADDR,
    VALUE
} arg_type;

typedef struct {
    uint8_t code;
    char *name;
} reg_t;

typedef struct {
    bool half_byte;
    uint8_t code;
    uint8_t argc;
    arg_type args[3];
    char *name;
} command_t;


#endif // _ARCH_H

