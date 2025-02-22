#include <stdio.h>
#include <string.h>
#include <parser.h>
#include <state.h>

int parse_args(int argc, char *argv[])
{
    state_t *state = get_state();
    enum parser_state s = INPUT_PATH;

    for (int i = 1; i < argc; i++)
    {
        switch (s)
        {
            case INPUT_PATH:
                if (strcmp(argv[i], "-o") == 0) s = OUTPUT_PATH;
                else if (strcmp(argv[i], "--output") == 0) s = OUTPUT_PATH;
                else if (strcmp(argv[i], "-h") == 0) state->help = true;
                else if (strcmp(argv[i], "--help") == 0) state->help = true;
                else if (strcmp(argv[i], "-v") == 0) state->version = true;
                else if (strcmp(argv[i], "--version") == 0) state->version = true;
                else
                {
                    if (state->ifpath == NULL) state->ifpath = argv[i];
                    else
                    {
                        printf("Unknown argument specified: %s\n", argv[i]);
                        return 1;
                    }
                }
                break;

            case OUTPUT_PATH:
                state->ofpath = argv[i];
                s = INPUT_PATH;
                break;

            default:
                break;
        }
    }

    if (state->ifpath == NULL)
    {
        printf("Input file is not specified\n");
        return 1;
    }
    else if (s == OUTPUT_PATH)
    {
        printf("Output file is not specified\n");
        return 1;
    }
    else if (argc < 2) state->help = true;

    return 0;
}
