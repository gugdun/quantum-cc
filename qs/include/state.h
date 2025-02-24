#ifndef _STATE_H
#define _STATE_H

#include <arch.h>

typedef struct {
    bool help;
    bool version;
    char *ifpath;
    char *ofpath;
    reg_t regs[16];
    command_t cmds[46];
    uint16_t addr;
    uint16_t org;
} state_t;

void init_state();
state_t *get_state();

#endif // _STATE_H
