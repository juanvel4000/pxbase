#include <pxbase/tty.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int hb_tty(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    if (isatty(STDIN_FILENO)) {
        printf("%s\n", ttyname(STDIN_FILENO));
        return EXIT_SUCCESS;
    }

    printf("not a tty\n");
    return EXIT_FAILURE;
}

int main(int argc, char **argv) { return hb_tty(argc, argv); }
