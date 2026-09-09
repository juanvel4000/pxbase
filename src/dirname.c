#include <hbase/common.h>
#include <hbase/dirname.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>

int get_dirname(int argc, char **argv)
{
    if (argc != 2)
        return EXIT_FAILURE;

    printf("%s\n", dirname(argv[1]));
    return EXIT_SUCCESS;
}

int main(int argc, char **argv)
{
    if (argc != 2)
        usage_exit(USAGE_STRING);

    return get_dirname(argc, argv);
}
