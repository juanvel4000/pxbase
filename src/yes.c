#include <hbase/yes.h>
#include <stdio.h>
#include <stdlib.h>

int hbase_yes(int argc, char **argv)
{
    static char *default_argv[] = {"yes", "y", NULL};

    if (argc <= 1) {
        argv = default_argv;
        argc = 2;
    }

    for (;;) {
        int i;
        for (i = 1; i < argc; i++) {
            if (i > 1)
                putchar(' ');

            fputs(argv[i], stdout);
        }

        putchar('\n');

        if (ferror(stdout))
            return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

int main(int argc, char **argv) { return hbase_yes(argc, argv); }
