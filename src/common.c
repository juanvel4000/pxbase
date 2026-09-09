#include <hbase/common.h>
#include <stdio.h>
#include <stdlib.h>

void usage_exit(const char *string)
{
    fprintf(stderr, "usage: %s\n", string);
    exit(EXIT_FAILURE);
}
