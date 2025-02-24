#include <stdio.h>
#include <state.h>
#include <args.h>
#include <help.h>
#include <parser.h>

int main(int argc, char *argv[])
{
    init_state();
    if (parse_args(argc, argv)) return 1;

    state_t *s = get_state();
    if (s->version)
    {
        print_version();
        return 0;
    }
    if (s->help)
    {
        print_help();
        return 0;
    }
    if (!s->ifpath)
    {
        printf("Input file is not specified\n");
        return 1;
    }

    object_t obj = (object_t) { 0 };
    if (parse_file(s->ifpath, &obj)) return 1;

    return 0;
}
