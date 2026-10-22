#include <pxbase/common.h>
#include <pxbase/logname.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int pxbase_logname(int argc, char **argv)
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

int main(int argc, char **argv) { return pxbase_logname(argc, argv); }
