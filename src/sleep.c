#include <errno.h>
#include <pxbase/common.h>
#include <pxbase/sleep.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int pxbase_sleep(int argc, char **argv)
{
    char *end;
    unsigned long seconds;
    if (argc != 2)
        pxbase_usage_exit(PXBASE_SLEEP_USAGE_STRING);

    errno = 0;
    seconds = strtoul(argv[1], &end, 10);

    if (errno != 0 || *end != '\0') {
        fprintf(stderr, "sleep: invalid time interval '%s'\n", argv[1]);
        return 1;
    }

    return sleep(seconds);
}

#ifndef PXBASE_MULTICALL

int main(int argc, char **argv) { return pxbase_sleep(argc, argv); }

#endif
