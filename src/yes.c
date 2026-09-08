#include <stdio.h>

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
    }

    return 0;
}

int main(int argc, char **argv)
{
    if (argc == 1)
        for (;;)
            puts("y");

    return yes(argc, argv);
}
