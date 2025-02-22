#include <stddef.h>
#include <state.h>

state_t state;

void init_state()
{
    state.help = false;
    state.version = false;
    state.ifpath = NULL;
    state.ofpath = NULL;
    state.addr = 0x0000;
    state.org = 0x0000;

    state.regs[0] = (reg_t) { 0x00, "R1" };
    state.regs[1] = (reg_t) { 0x01, "R2" };
    state.regs[2] = (reg_t) { 0x02, "R3" };
    state.regs[3] = (reg_t) { 0x03, "R4" };
    state.regs[4] = (reg_t) { 0x04, "R5" };
    state.regs[5] = (reg_t) { 0x05, "R6" };
    state.regs[6] = (reg_t) { 0x06, "R7" };
    state.regs[7] = (reg_t) { 0x07, "R8" };
    state.regs[8] = (reg_t) { 0x08, "R9" };
    state.regs[9] = (reg_t) { 0x09, "R10" };
    state.regs[10] = (reg_t) { 0x0A, "R11" };
    state.regs[11] = (reg_t) { 0x0B, "R12" };
    state.regs[12] = (reg_t) { 0x0C, "SP" };
    state.regs[13] = (reg_t) { 0x0D, "PT" };
    state.regs[14] = (reg_t) { 0x0E, "CR" };
    state.regs[15] = (reg_t) { 0x0F, "PC" };

    state.cmds[0] = (command_t) {
        .half_byte = false,
        .code = 0x00,
        .argc = 0,
        .args = { 0 },
        .name = "NOP"
    };
    state.cmds[1] = (command_t) {
        .half_byte = false,
        .code = 0x10,
        .argc = 2,
        .args = { REG, REG },
        .name = "ADD"
    };
    state.cmds[2] = (command_t) {
        .half_byte = false,
        .code = 0x11,
        .argc = 2,
        .args = { REG, REG },
        .name = "ADDS"
    };
    state.cmds[3] = (command_t) {
        .half_byte = false,
        .code = 0x12,
        .argc = 2,
        .args = { REG, REG },
        .name = "SUB"
    };
    state.cmds[4] = (command_t) {
        .half_byte = false,
        .code = 0x13,
        .argc = 2,
        .args = { REG, REG },
        .name = "SUBS"
    };
    state.cmds[5] = (command_t) {
        .half_byte = false,
        .code = 0x14,
        .argc = 2,
        .args = { REG, REG },
        .name = "MUL"
    };
    state.cmds[6] = (command_t) {
        .half_byte = false,
        .code = 0x15,
        .argc = 2,
        .args = { REG, REG },
        .name = "MULS"
    };
    state.cmds[7] = (command_t) {
        .half_byte = false,
        .code = 0x16,
        .argc = 2,
        .args = { REG, REG },
        .name = "DIV"
    };
    state.cmds[8] = (command_t) {
        .half_byte = false,
        .code = 0x17,
        .argc = 2,
        .args = { REG, REG },
        .name = "DIVS"
    };
    state.cmds[9] = (command_t) {
        .half_byte = false,
        .code = 0x18,
        .argc = 2,
        .args = { REG, REG },
        .name = "MOD"
    };
    state.cmds[10] = (command_t) {
        .half_byte = false,
        .code = 0x19,
        .argc = 1,
        .args = { REG },
        .name = "INV"
    };
    state.cmds[11] = (command_t) {
        .half_byte = false,
        .code = 0x1A,
        .argc = 2,
        .args = { REG, REG },
        .name = "SHL"
    };
    state.cmds[12] = (command_t) {
        .half_byte = false,
        .code = 0x1B,
        .argc = 2,
        .args = { REG, REG },
        .name = "SHR"
    };
    state.cmds[13] = (command_t) {
        .half_byte = false,
        .code = 0x1C,
        .argc = 1,
        .args = { REG },
        .name = "NOT"
    };
    state.cmds[14] = (command_t) {
        .half_byte = false,
        .code = 0x1D,
        .argc = 2,
        .args = { REG, REG },
        .name = "AND"
    };
    state.cmds[15] = (command_t) {
        .half_byte = false,
        .code = 0x1E,
        .argc = 2,
        .args = { REG, REG },
        .name = "OR"
    };
    state.cmds[16] = (command_t) {
        .half_byte = false,
        .code = 0x1F,
        .argc = 2,
        .args = { REG, REG },
        .name = "XOR"
    };
    state.cmds[17] = (command_t) {
        .half_byte = false,
        .code = 0x20,
        .argc = 1,
        .args = { ADDR },
        .name = "JMP"
    };
    state.cmds[18] = (command_t) {
        .half_byte = false,
        .code = 0x21,
        .argc = 3,
        .args = { REG, REG, ADDR },
        .name = "JL"
    };
    state.cmds[19] = (command_t) {
        .half_byte = false,
        .code = 0x22,
        .argc = 3,
        .args = { REG, REG, ADDR },
        .name = "JLE"
    };
    state.cmds[20] = (command_t) {
        .half_byte = false,
        .code = 0x23,
        .argc = 3,
        .args = { REG, REG, ADDR },
        .name = "JE"
    };
    state.cmds[21] = (command_t) {
        .half_byte = false,
        .code = 0x24,
        .argc = 3,
        .args = { REG, REG, ADDR },
        .name = "JNE"
    };
    state.cmds[22] = (command_t) {
        .half_byte = false,
        .code = 0x25,
        .argc = 3,
        .args = { REG, REG, ADDR },
        .name = "JGE"
    };
    state.cmds[23] = (command_t) {
        .half_byte = false,
        .code = 0x26,
        .argc = 3,
        .args = { REG, REG, ADDR },
        .name = "JG"
    };
    state.cmds[24] = (command_t) {
        .half_byte = false,
        .code = 0x31,
        .argc = 2,
        .args = { REG, REG },
        .name = "LDB"
    };
    state.cmds[25] = (command_t) {
        .half_byte = false,
        .code = 0x32,
        .argc = 2,
        .args = { REG, REG },
        .name = "LDW"
    };
    state.cmds[26] = (command_t) {
        .half_byte = false,
        .code = 0x33,
        .argc = 2,
        .args = { REG, REG },
        .name = "STB"
    };
    state.cmds[27] = (command_t) {
        .half_byte = false,
        .code = 0x34,
        .argc = 2,
        .args = { REG, REG },
        .name = "STW"
    };
    state.cmds[28] = (command_t) {
        .half_byte = true,
        .code = 0x40,
        .argc = 2,
        .args = { REG, ADDR },
        .name = "LDB"
    };
    state.cmds[29] = (command_t) {
        .half_byte = true,
        .code = 0x50,
        .argc = 2,
        .args = { REG, ADDR },
        .name = "LDW"
    };
    state.cmds[30] = (command_t) {
        .half_byte = true,
        .code = 0x60,
        .argc = 2,
        .args = { REG, VALUE },
        .name = "LDB"
    };
    state.cmds[31] = (command_t) {
        .half_byte = true,
        .code = 0x70,
        .argc = 2,
        .args = { REG, VALUE },
        .name = "LDW"
    };
    state.cmds[32] = (command_t) {
        .half_byte = true,
        .code = 0x80,
        .argc = 2,
        .args = { REG, ADDR },
        .name = "STB"
    };
    state.cmds[33] = (command_t) {
        .half_byte = true,
        .code = 0x90,
        .argc = 2,
        .args = { REG, ADDR },
        .name = "STW"
    };
    state.cmds[34] = (command_t) {
        .half_byte = true,
        .code = 0xA0,
        .argc = 1,
        .args = { REG },
        .name = "PUSH"
    };
    state.cmds[35] = (command_t) {
        .half_byte = true,
        .code = 0xB0,
        .argc = 1,
        .args = { REG },
        .name = "POP"
    };
    state.cmds[36] = (command_t) {
        .half_byte = true,
        .code = 0xC0,
        .argc = 1,
        .args = { REG },
        .name = "CALL"
    };
    state.cmds[37] = (command_t) {
        .half_byte = false,
        .code = 0x3F,
        .argc = 1,
        .args = { ADDR },
        .name = "CALL"
    };
    state.cmds[38] = (command_t) {
        .half_byte = false,
        .code = 0x35,
        .argc = 0,
        .args = { 0 },
        .name = "RET"
    };
    state.cmds[39] = (command_t) {
        .half_byte = false,
        .code = 0x36,
        .argc = 2,
        .args = { REG, REG },
        .name = "MOV"
    };
    state.cmds[40] = (command_t) {
        .half_byte = false,
        .code = 0x37,
        .argc = 1,
        .args = { VALUE },
        .name = "INT"
    };
    state.cmds[41] = (command_t) {
        .half_byte = true,
        .code = 0xD0,
        .argc = 1,
        .args = { REG },
        .name = "INC"
    };
    state.cmds[42] = (command_t) {
        .half_byte = true,
        .code = 0xE0,
        .argc = 1,
        .args = { REG },
        .name = "DEC"
    };
    state.cmds[43] = (command_t) {
        .half_byte = false,
        .code = 0xFF,
        .argc = 0,
        .args = { 0 },
        .name = "HLT"
    };
}

state_t *get_state()
{
    return &state;
}
