#include <hbase/dirname.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>

static void usage(void)
{
    fprintf(stderr, "usage: dirname path\n");
    exit(EXIT_FAILURE);
}

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
        usage();

    return get_dirname(argc, argv);
}
