#include <errno.h>
#include <pxbase/common.h>
#include <pxbase/link.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int pxbase_link(int argc, char **argv)
{
    const char *target;
    const char *linkname;

    if (argc != 3)
        pxbase_usage_exit(PXBASE_LINK_USAGE_STRING);

    target = argv[1];
    linkname = argv[2];

    if (link(target, linkname) != 0) {
        fprintf(stderr, "link: %s: %s: %s\n", target, linkname,
                strerror(errno));
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

#ifndef PXBASE_MULTICALL

int main(int argc, char **argv) { return pxbase_link(argc, argv); }

#endif
