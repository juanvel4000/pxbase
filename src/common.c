#include <pxbase/common.h>
#include <stdio.h>
#include <stdlib.h>

void pxbase_usage_exit(const char *string)
{
    fprintf(stderr, "usage: %s\n", string);
    exit(EXIT_FAILURE);
}
