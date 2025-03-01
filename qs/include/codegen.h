#ifndef _CODEGEN_H
#define _CODEGEN_H

#include <arch.h>
#include <obj.h>

int emit(command_t *cmd, char *arg1, char *arg2, char *arg3, object_t *obj);

#endif // _CODEGEN_H
