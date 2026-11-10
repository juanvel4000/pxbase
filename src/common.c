#include <errno.h>
#include <pxbase/common.h>
#include <stdio.h>
#include <stdlib.h>

void pxbase_usage_exit(const char *string)
{
    fprintf(stderr, "usage: %s\n", string);
    exit(EXIT_FAILURE);
}

int parse_mode(const char *s, mode_t *out)
{
    char *end;
    long value;

    errno = 0;
    value = strtol(s, &end, 8);

    if (errno == ERANGE)
        return -1;

    if (end == s)
        return -1;

    if (*end != '\0')
        return -1;

    if (value < 0)
        return -1;

    if (value > 07777)
        return -1;

    *out = value;

    return 0;
}
