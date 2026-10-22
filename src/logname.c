#include <hbase/common.h>
#include <hbase/logname.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int hbase_logname(int argc, char **argv)
{
    char *p;

    (void)argc;
    (void)argv;

    if ((p = getlogin()) == NULL) {
        perror("logname");
        return EXIT_FAILURE;
    }
    printf("%s\n", p);
    return EXIT_SUCCESS;
}

int main(int argc, char **argv) { return hbase_logname(argc, argv); }
