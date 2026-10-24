#include <errno.h>
#include <pxbase/common.h>
#include <pxbase/unlink.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int pxbase_unlink(int argc, char **argv)
{

    if (argc != 2)
        pxbase_usage_exit(PXBASE_UNLINK_USAGE_STRING);

    if (unlink(argv[1]) != 0) {
        fprintf(stderr, "unlink: %s: %s\n", argv[1], strerror(errno));
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

#ifndef PXBASE_MULTICALL

int main(int argc, char **argv) { return pxbase_unlink(argc, argv); }

#endif
