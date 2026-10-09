#include <errno.h>
#include <hbase/common.h>
#include <hbase/rmdir.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int hbase_rmdir(int argc, char **argv)
{
    int i;
    int ret;

    ret = EXIT_SUCCESS;

    if (argc == 1)
        hbase_usage_exit(HBASE_RMDIR_USAGE_STRING);

    for (i = 1; i < argc; i++) {
        if (rmdir(argv[i]) != 0) {
            fprintf(stderr, "rmdir: failed to remove '%s': %s\n", argv[i],
                    strerror(errno));
            ret = EXIT_FAILURE;
        }
    }

    return ret;
}

int main(int argc, char **argv) { return hbase_rmdir(argc, argv); }
