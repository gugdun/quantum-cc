#ifndef _ARGS_H
#define _ARGS_H

enum parser_state
{
    INPUT_PATH,
    OUTPUT_PATH
};

int parse_args(int argc, char *argv[]);

#endif // _ARGS_H
