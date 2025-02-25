#ifndef _STATE_H
#define _STATE_H

#include <arch.h>

#define REGS 16
#define CMDS 47

typedef struct {
    bool help;
    bool version;
    char *ifpath;
    char *ofpath;
    reg_t regs[REGS];
    command_t cmds[CMDS];
    uint16_t addr;
    uint16_t org;
} state_t;

void init_state();
state_t *get_state();

#endif // _STATE_H
