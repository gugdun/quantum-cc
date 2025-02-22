#include <stdio.h>
#include <config.h>
#include <help.h>

void print_version()
{
    printf(
        "qs version %d.%d.%d by %s\n",
        VERSION_MAJOR,
        VERSION_MINOR,
        VERSION_PATCH,
        DEVELOPER
    );
}

void print_help()
{
    printf("Usage: qs [options] file\nOptions:\n");
    printf("  -h, --help    Print this message and exit.\n");
    printf("  -v, --version Print compiler version and exit.\n");
    printf("  -o, --output  Specify output file path.\n");
}
