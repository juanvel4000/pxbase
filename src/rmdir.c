#include <errno.h>
#include <pxbase/common.h>
#include <pxbase/rmdir.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int pxbase_rmdir(int argc, char **argv)
{
    int i;
    int ret;

    ret = EXIT_SUCCESS;

    if (argc == 1)
        pxbase_usage_exit(PXBASE_RMDIR_USAGE_STRING);

    for (i = 1; i < argc; i++) {
        if (rmdir(argv[i]) != 0) {
            fprintf(stderr, "rmdir: failed to remove '%s': %s\n", argv[i],
                    strerror(errno));
            ret = EXIT_FAILURE;
        }
    }

    return ret;
}

#ifndef PXBASE_MULTICALL

int main(int argc, char **argv) { return pxbase_rmdir(argc, argv); }

#endif
