#include <libgen.h>
#include <pxbase/common.h>
#include <pxbase/dirname.h>
#include <stdio.h>
#include <stdlib.h>

int pxbase_dirname(int argc, char **argv)
{
    if (argc != 2)
        pxbase_usage_exit(PXBASE_DIRNAME_USAGE_STRING);
    printf("%s\n", (dirname)(argv[1]));
    return EXIT_SUCCESS;
}

#ifndef PXBASE_MULTICALL

int main(int argc, char **argv) { return pxbase_dirname(argc, argv); }

#endif
