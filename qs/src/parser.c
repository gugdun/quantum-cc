#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <parser.h>
#include <toupper.h>
#include <getdelim.h>
#include <obj.h>
#include <state.h>
#include <codegen.h>

#define LINE_ALLOC_SIZE 32
#define DELIMITERS " \n\t,"

int parse_line(int number, char *line, object_t *obj)
{
#ifdef DEBUG
    printf("%5d | %s\n", number, line);
#endif
    state_t *state = get_state();
    
    char *cmd = strtok(line, DELIMITERS);
    if (!cmd || *cmd == ';') return 0;
    
    size_t len = strlen(cmd);
    if (cmd[len - 1] == ':')
    {
        cmd[len - 1] = 0;
        add_tag(cmd, state->addr + state->org, obj);
        return 0;
    }
    
    to_upper(cmd);
    command_t *command = NULL;
    for (int i = 0; i < CMDS; ++i)
    {
        if (!strcmp(state->cmds[i].name, cmd))
        {
            command = &state->cmds[i];
            break;
        }
    }

    if (!command)
    {
        printf("Unknown command: %s\n", cmd);
        return 1;
    }

#ifdef DEBUG
    printf("TOKENS| cmd: %s", cmd);
#endif

    char *arg1 = NULL;
    char *arg2 = NULL;
    char *arg3 = NULL;

    switch (command->argc)
    {
        case 1:
            if (command->code == 0) arg1 = strtok(NULL, "");
            else arg1 = strtok(NULL, DELIMITERS);
#ifdef DEBUG
            printf(", arg1: %s", arg1);
#endif
            break;

        case 2:
            arg1 = strtok(NULL, DELIMITERS);
            arg2 = strtok(NULL, DELIMITERS);
#ifdef DEBUG
            printf(", arg1: %s, arg2: %s", arg1, arg2);
#endif
            break;

        case 3:
            arg1 = strtok(NULL, DELIMITERS);
            arg2 = strtok(NULL, DELIMITERS);
            arg3 = strtok(NULL, DELIMITERS);
#ifdef DEBUG
            printf(", arg1: %s, arg2: %s, arg3: %s", arg1, arg2, arg3);
#endif
            break;

        default:
            break;
    }
    
#ifdef DEBUG
    putchar('\n');
#endif

    return emit(command, arg1, arg2, arg3, obj);
}

int parse_file(char *path, object_t *obj)
{
    FILE *file = fopen(path, "r");
    if (!file)
    {
        printf("File not found: %s\n", path);
        return 1;
    }

    ssize_t read = 0;
    int exit_code = 0;
    int number = 1;
    size_t len = LINE_ALLOC_SIZE;
    char *line = (char *)malloc(LINE_ALLOC_SIZE);
    
    while ((read = qcc_getline(&line, &len, file)) != -1)
    {
        if (read > 0 && (line[read - 1] == '\n' || line[read - 1])) line[read - 1] = 0;
        if (read > 1 && line[read - 2] == '\r') line[read - 2] = 0;
        if (parse_line(number, line, obj))
        {
            exit_code = 1;
            break;
        }
        ++number;
    }

    free(line);
    fclose(file);
    
    return exit_code;
}

unsigned long parse_address(char *arg)
{
    size_t len = strlen(arg);
    int base = 10;
    if (len >= 2 && arg[0] == '0' && arg[1] == 'x')
    {
        arg += 2;
        base = 16;
    }
    else if (arg[len - 1] == 'h')
    {
        arg[len - 1] = 0;
        base = 16;
    }
    else if (arg[len - 1] == 'o')
    {
        arg[len - 1] = 0;
        base = 8;
    }
    else if (arg[len - 1] == 'b')
    {
        arg[len - 1] = 0;
        base = 2;
    }
    return strtoul(arg, NULL, base);
}

long parse_value(char *arg)
{
    size_t len = strlen(arg);
    int base = 10;
    if (len >= 2 && arg[0] == '0' && arg[1] == 'x')
    {
        arg += 2;
        base = 16;
    }
    else if (arg[len - 1] == 'h')
    {
        arg[len - 1] = 0;
        base = 16;
    }
    else if (arg[len - 1] == 'o')
    {
        arg[len - 1] = 0;
        base = 8;
    }
    else if (arg[len - 1] == 'b')
    {
        arg[len - 1] = 0;
        base = 2;
    }
    return strtol(arg, NULL, base);
}
