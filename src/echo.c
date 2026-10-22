#include <pxbase/common.h>
#include <pxbase/echo.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int pxbase_echo(int argc, char **argv)
{
    int start = 1;
    int newline = 1;
    int i;

    if (argc >= 2 && strcmp(argv[1], "-n") == 0) {
        start = 2;
        newline = 0;
    }

    for (i = start; i < argc; i++) {
        if (i > start)
            putchar(' ');

        fputs(argv[i], stdout);
    }

    if (newline)
        putchar('\n');

    if (ferror(stdout))
        return EXIT_FAILURE;

    return EXIT_SUCCESS;
}

int main(int argc, char **argv) { return pxbase_echo(argc, argv); }
