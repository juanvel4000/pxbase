#include <hbase/yes.h>
#include <stdio.h>
#include <stdlib.h>

int yes(int argc, char **argv)
{
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

int main(int argc, char **argv)
{
    if (argc == 1) {
        argv[1] = "y";
        argc = 2;
    }

    return yes(argc, argv);
}
