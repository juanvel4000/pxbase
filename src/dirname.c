#include <hbase/common.h>
#include <hbase/dirname.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>

int hbase_dirname(int argc, char **argv)
{
    if (argc != 2)
        hbase_usage_exit(HBASE_DIRNAME_USAGE_STRING);
    printf("%s\n", (dirname)(argv[1]));
    return EXIT_SUCCESS;
}

int main(int argc, char **argv) { return hbase_dirname(argc, argv); }
