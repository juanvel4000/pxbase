#include <pxbase/false.h>
#include <stdlib.h>

int pxbase_false(int argc, char **argv)
{
    (void)argc;
    (void)argv;
    return EXIT_FAILURE;
}

#ifndef PXBASE_MULTICALL

int main(int argc, char **argv) { return pxbase_false(argc, argv); }

#endif
