#include <stdio.h>
#include <config.h>
#include <state.h>
#include <parser.h>

int main(int argc, char *argv[])
{
    init_state();
    if (parse_args(argc, argv)) return 1;

    state_t *s = get_state();
    if (s->version)
    {
        printf(
            "qs version %d.%d.%d by %s\n",
            VERSION_MAJOR,
            VERSION_MINOR,
            VERSION_PATCH,
            DEVELOPER
        );
        return 0;
    }

    return 0;
}
