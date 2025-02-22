#ifndef _PARSER_H
#define _PARSER_H

enum parser_state
{
    INPUT_PATH,
    OUTPUT_PATH
};

int parse_args(int argc, char *argv[]);

#endif // _PARSER_H
