#include <stdlib.h>
#include <unistd.h>

int hbase_sync(int argc, char **argv)
{
    (void)argc;
    (void)argv;
    sync();
    return EXIT_SUCCESS;
}

int main(int argc, char **argv) { return hbase_sync(argc, argv); }
