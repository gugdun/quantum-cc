#include <ctype.h>
#include <toupper.h>

void to_upper(char *str)
{
    char *s = str;
    while (*s)
    {
        *s = toupper((unsigned char)*s);
        ++s;
    }
}
