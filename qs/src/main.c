#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <config.h>

// Object file format

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

// Architecture

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

// Compiler

int main(int argc, char *argv[])
{
    reg_t regs[] = {
        { 0x00, "R1" },
        { 0x01, "R2" },
        { 0x02, "R3" },
        { 0x03, "R4" },
        { 0x04, "R5" },
        { 0x05, "R6" },
        { 0x06, "R7" },
        { 0x07, "R8" },
        { 0x08, "R9" },
        { 0x09, "R10" },
        { 0x0A, "R11" },
        { 0x0B, "R12" },
        { 0x0C, "SP" },
        { 0x0D, "PT" },
        { 0x0E, "CR" },
        { 0x0F, "PC" }
    };

    command_t commands[] = {
        {
            .half_byte = false,
            .code = 0x00,
            .argc = 0,
            .args = { 0 },
            .name = "NOP"
        },
        {
            .half_byte = false,
            .code = 0x10,
            .argc = 2,
            .args = { REG, REG },
            .name = "ADD"
        },
        {
            .half_byte = false,
            .code = 0x11,
            .argc = 2,
            .args = { REG, REG },
            .name = "ADDS"
        },
        {
            .half_byte = false,
            .code = 0x12,
            .argc = 2,
            .args = { REG, REG },
            .name = "SUB"
        },
        {
            .half_byte = false,
            .code = 0x13,
            .argc = 2,
            .args = { REG, REG },
            .name = "SUBS"
        },
        {
            .half_byte = false,
            .code = 0x14,
            .argc = 2,
            .args = { REG, REG },
            .name = "MUL"
        },
        {
            .half_byte = false,
            .code = 0x15,
            .argc = 2,
            .args = { REG, REG },
            .name = "MULS"
        },
        {
            .half_byte = false,
            .code = 0x16,
            .argc = 2,
            .args = { REG, REG },
            .name = "DIV"
        },
        {
            .half_byte = false,
            .code = 0x17,
            .argc = 2,
            .args = { REG, REG },
            .name = "DIVS"
        },
        {
            .half_byte = false,
            .code = 0x18,
            .argc = 2,
            .args = { REG, REG },
            .name = "MOD"
        },
        {
            .half_byte = false,
            .code = 0x19,
            .argc = 1,
            .args = { REG },
            .name = "INV"
        },
        {
            .half_byte = false,
            .code = 0x1A,
            .argc = 2,
            .args = { REG, REG },
            .name = "SHL"
        },
        {
            .half_byte = false,
            .code = 0x1B,
            .argc = 2,
            .args = { REG, REG },
            .name = "SHR"
        },
        {
            .half_byte = false,
            .code = 0x1C,
            .argc = 1,
            .args = { REG },
            .name = "NOT"
        },
        {
            .half_byte = false,
            .code = 0x1D,
            .argc = 2,
            .args = { REG, REG },
            .name = "AND"
        },
        {
            .half_byte = false,
            .code = 0x1E,
            .argc = 2,
            .args = { REG, REG },
            .name = "OR"
        },
        {
            .half_byte = false,
            .code = 0x1F,
            .argc = 2,
            .args = { REG, REG },
            .name = "XOR"
        },
        {
            .half_byte = false,
            .code = 0x20,
            .argc = 1,
            .args = { ADDR },
            .name = "JMP"
        },
        {
            .half_byte = false,
            .code = 0x21,
            .argc = 3,
            .args = { REG, REG, ADDR },
            .name = "JL"
        },
        {
            .half_byte = false,
            .code = 0x22,
            .argc = 3,
            .args = { REG, REG, ADDR },
            .name = "JLE"
        },
        {
            .half_byte = false,
            .code = 0x23,
            .argc = 3,
            .args = { REG, REG, ADDR },
            .name = "JE"
        },
        {
            .half_byte = false,
            .code = 0x24,
            .argc = 3,
            .args = { REG, REG, ADDR },
            .name = "JNE"
        },
        {
            .half_byte = false,
            .code = 0x25,
            .argc = 3,
            .args = { REG, REG, ADDR },
            .name = "JGE"
        },
        {
            .half_byte = false,
            .code = 0x26,
            .argc = 3,
            .args = { REG, REG, ADDR },
            .name = "JG"
        },
        {
            .half_byte = false,
            .code = 0x31,
            .argc = 2,
            .args = { REG, REG },
            .name = "LDB"
        },
        {
            .half_byte = false,
            .code = 0x32,
            .argc = 2,
            .args = { REG, REG },
            .name = "LDW"
        },
        {
            .half_byte = false,
            .code = 0x33,
            .argc = 2,
            .args = { REG, REG },
            .name = "STB"
        },
        {
            .half_byte = false,
            .code = 0x34,
            .argc = 2,
            .args = { REG, REG },
            .name = "STW"
        },
        {
            .half_byte = true,
            .code = 0x40,
            .argc = 2,
            .args = { REG, ADDR },
            .name = "LDB"
        },
        {
            .half_byte = true,
            .code = 0x50,
            .argc = 2,
            .args = { REG, ADDR },
            .name = "LDW"
        },
        {
            .half_byte = true,
            .code = 0x60,
            .argc = 2,
            .args = { REG, VALUE },
            .name = "LDB"
        },
        {
            .half_byte = true,
            .code = 0x70,
            .argc = 2,
            .args = { REG, VALUE },
            .name = "LDW"
        },
        {
            .half_byte = true,
            .code = 0x80,
            .argc = 2,
            .args = { REG, ADDR },
            .name = "STB"
        },
        {
            .half_byte = true,
            .code = 0x90,
            .argc = 2,
            .args = { REG, ADDR },
            .name = "STW"
        },
        {
            .half_byte = true,
            .code = 0xA0,
            .argc = 1,
            .args = { REG },
            .name = "PUSH"
        },
        {
            .half_byte = true,
            .code = 0xB0,
            .argc = 1,
            .args = { REG },
            .name = "POP"
        },
        {
            .half_byte = true,
            .code = 0xC0,
            .argc = 1,
            .args = { REG },
            .name = "CALL"
        },
        {
            .half_byte = false,
            .code = 0x3F,
            .argc = 1,
            .args = { ADDR },
            .name = "CALL"
        },
        {
            .half_byte = false,
            .code = 0x35,
            .argc = 0,
            .args = { 0 },
            .name = "RET"
        },
        {
            .half_byte = false,
            .code = 0x36,
            .argc = 2,
            .args = { REG, REG },
            .name = "MOV"
        },
        {
            .half_byte = false,
            .code = 0x37,
            .argc = 1,
            .args = { VALUE },
            .name = "INT"
        },
        {
            .half_byte = true,
            .code = 0xD0,
            .argc = 1,
            .args = { REG },
            .name = "INC"
        },
        {
            .half_byte = true,
            .code = 0xE0,
            .argc = 1,
            .args = { REG },
            .name = "DEC"
        },
        {
            .half_byte = false,
            .code = 0xFF,
            .argc = 0,
            .args = { 0 },
            .name = "HLT"
        }
    };

    printf(
        "qs version %d.%d.%d by %s\n",
        VERSION_MAJOR,
        VERSION_MINOR,
        VERSION_PATCH,
        DEVELOPER
    );

    return 0;
}

