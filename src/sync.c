#include <pxbase/common.h>
#include <pxbase/sync.h>
#include <stdlib.h>
#include <unistd.h>

int pxbase_sync(int argc, char **argv)
{
    (void)argc;
    (void)argv;
    sync();
    return EXIT_SUCCESS;
}

int main(int argc, char **argv) { return pxbase_sync(argc, argv); }
