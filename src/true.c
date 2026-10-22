#include <pxbase/common.h>
#include <pxbase/true.h>
#include <stdlib.h>

int pxbase_true(int argc, char **argv)
{
    (void)argc;
    (void)argv;
    return EXIT_SUCCESS;
}

#ifndef PXBASE_MULTICALL

int main(int argc, char **argv) { return pxbase_true(argc, argv); }

#endif
