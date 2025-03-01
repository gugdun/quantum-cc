#include <stdio.h>
#include <codegen.h>
#include <parser.h>
#include <state.h>

int emit(command_t *cmd, char *arg1, char *arg2, char *arg3, object_t *obj)
{
    state_t *s = get_state();
    switch (cmd->argc)
    {
        case 0:
            break;
        
        case 1:
            if (cmd->args[0] == ORG)
            {
                s->org = (uint16_t)parse_address(arg1);
                s->addr = 0;
            }
            break;
        
        case 2:
            break;
        
        case 3:
            break;
        
        default:
            printf("Not implemented: argc = %d\n", cmd->argc);
            return 1;
    }
    return 0;
}
