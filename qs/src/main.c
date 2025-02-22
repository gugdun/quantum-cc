#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <config.h>
#include <state.h>

int main(int argc, char *argv[])
{
    init_state();

    printf(
        "qs version %d.%d.%d by %s\n",
        VERSION_MAJOR,
        VERSION_MINOR,
        VERSION_PATCH,
        DEVELOPER
    );

    return 0;
}

