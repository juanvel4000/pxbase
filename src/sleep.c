#include <errno.h>
#include <hbase/common.h>
#include <hbase/sleep.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int hbase_sleep(char **argv, int argc)
{
    char *end;
    unsigned long seconds;
    if (argc != 2)
        hbase_usage_exit(HBASE_SLEEP_USAGE_STRING);

    errno = 0;
    seconds = strtoul(argv[1], &end, 10);

    if (errno != 0 || *end != '\0') {
        fprintf(stderr, "sleep: invalid time interval '%s'\n", argv[1]);
        return 1;
    }

    return sleep(seconds);
}

int main(int argc, char **argv) { return hbase_sleep(argv, argc); }
