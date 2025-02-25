#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <memory.h>
#include <parser.h>
#include <state.h>
#include <getdelim.h>

#define LINE_ALLOC_SIZE 32
#define DATA_CHUNK_SIZE 256
#define DELIMITERS " \n\t,"

void strtou(char *str);
void add_tag(char *name, uint16_t addr, object_t *obj);
void add_link(char *name, uint16_t addr, object_t *obj);
void add_data(uint8_t *chunk, uint16_t size, object_t *obj);

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
    
    strtou(cmd);
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

    if (command->argc == 0)
    {
#ifdef DEBUG
        printf("TOKENS| cmd: %s\n", cmd);
#endif
    }
    else if (command->argc == 1)
    {
        char *arg1 = NULL;
        if (command->code == 0) arg1 = strtok(NULL, "");
        else arg1 = strtok(NULL, DELIMITERS);
        size_t l1 = strlen(arg1);
#ifdef DEBUG
        printf("TOKENS| cmd: %s, arg1: %s\n", cmd, arg1);
#endif

        if (command->args[0] == ORG)
        {
            int base = 10;
            if (l1 >= 2 && arg1[0] == '0' && arg1[1] == 'x')
            {
                arg1 += 2;
                base = 16;
            }
            if (arg1[l1 - 1] == 'h')
            {
                arg1[l1 - 1] = 0;
                base = 16;
            }
            if (arg1[l1 - 1] == 'o')
            {
                arg1[l1 - 1] = 0;
                base = 8;
            }
            if (arg1[l1 - 1] == 'b')
            {
                arg1[l1 - 1] = 0;
                base = 2;
            }
            state->org = (uint16_t)strtoul(arg1, NULL, base);
            state->addr = 0;
        }
    }
    else if (command->argc == 2)
    {
        char *arg1 = strtok(NULL, DELIMITERS);
        char *arg2 = strtok(NULL, DELIMITERS);
#ifdef DEBUG
        printf("TOKENS| cmd: %s, arg1: %s, arg2: %s\n", cmd, arg1, arg2);
#endif
    }
    else if (command->argc == 3)
    {
        char *arg1 = strtok(NULL, DELIMITERS);
        char *arg2 = strtok(NULL, DELIMITERS);
        char *arg3 = strtok(NULL, DELIMITERS);
#ifdef DEBUG
        printf("TOKENS| cmd: %s, arg1: %s, arg2: %s, arg3: %s\n", cmd, arg1, arg2, arg3);
#endif
    }
    
    return 0;
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

void add_tag(char *name, uint16_t addr, object_t *obj)
{
    if (!obj->tags) obj->tags = (tag_t *)malloc(sizeof(tag_t));
    else obj->tags = (tag_t *)realloc(obj->tags, sizeof(tag_t) * (obj->tag_count + 1));
    tag_t *last_tag = &obj->tags[obj->tag_count];
    last_tag->addr = addr;
    last_tag->name_size = (uint8_t)strlen(name);
    last_tag->name = (char *)malloc(last_tag->name_size + 1);
    strcpy(last_tag->name, (const char*)name);
    ++obj->tag_count;
#ifdef DEBUG
    printf("FNCALL| add_tag(%s, 0x%04X)\n", last_tag->name, last_tag->addr);
#endif
}

void add_link(char *name, uint16_t addr, object_t *obj)
{
    if (!obj->links) obj->links = (link_t *)malloc(sizeof(link_t));
    else obj->links = (link_t *)realloc(obj->links, sizeof(link_t) * (obj->link_count + 1));
    link_t *last_link = &obj->links[obj->link_count];
    last_link->addr = addr;
    last_link->name_size = (uint8_t)strlen(name);
    last_link->name = (char *)malloc(last_link->name_size + 1);
    strcpy(last_link->name, (const char*)name);
    ++obj->link_count;
#ifdef DEBUG
    printf("FNCALL| add_link(%s, 0x%04X)\n", last_link->name, last_link->addr);
#endif
}

void add_data(uint8_t *chunk, uint16_t size, object_t *obj)
{
    if (!obj->data)
    {
        obj->data = (uint8_t *)malloc(DATA_CHUNK_SIZE);
        obj->alloc_size = DATA_CHUNK_SIZE;
        obj->size = 0;
    }
    else if (obj->size + size > obj->alloc_size)
    {
        obj->data = (uint8_t *)realloc(obj->data, obj->alloc_size + DATA_CHUNK_SIZE);
        obj->alloc_size += DATA_CHUNK_SIZE;
    }
    memcpy((void *)&obj->data[obj->size], (void *)chunk, (size_t)size);
    obj->size += size;
#ifdef DEBUG
    printf("FNCALL| add_data(0x%04X)\n", size);
#endif
}

void strtou(char *str)
{
    char *s = str;
    while (*s)
    {
        *s = toupper((unsigned char)*s);
        ++s;
    }
}
