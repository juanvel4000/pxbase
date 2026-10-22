#include <errno.h>
#include <pxbase/common.h>
#include <pxbase/env.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

extern char **environ;

int pxbase_env(int argc, char **argv)
{
    char **ep;
    char *p;
    char *cleanenv[1];
    int opt;

    while ((opt = getopt(argc, argv, "i")) != -1) {
        switch (opt) {
        case 'i':
            environ = cleanenv;
            cleanenv[0] = NULL;
            break;
        case '?':
            pxbase_usage_exit(PXBASE_ENV_USAGE_STRING);
        }
    }

    for (argv += optind; *argv && (p = strchr(*argv, '=')); argv++) {
        if (setenv(*argv, ++p, 1) != 0) {
            perror("env");
            return EXIT_FAILURE;
        }
    }

    if (*argv) {
        execvp(*argv, argv);
        fprintf(stderr, "env: %s: %s\n", *argv, strerror(errno));
        return EXIT_FAILURE;
    }

    for (ep = environ; *ep; ep++)
        printf("%s\n", *ep);

    return EXIT_SUCCESS;
}

#ifndef PXBASE_MULTICALL

int main(int argc, char **argv) { return pxbase_env(argc, argv); }

#endif
