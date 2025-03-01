#ifndef _PARSER_H
#define _PARSER_H

#include <obj.h>

int parse_file(char *path, object_t *obj);
unsigned long parse_address(char *arg);
long parse_value(char *arg);

#endif // _PARSER_H

