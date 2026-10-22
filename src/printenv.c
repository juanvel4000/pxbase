#include <hbase/common.h>
#include <hbase/printenv.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

extern char **environ;

int hbase_printenv(int argc, char **argv)
{
    char *cp;
    char **ep;
    size_t len;
    int opt;

    while ((opt = getopt(argc, argv, "")) != -1)
        switch (opt)
        case '?':
            hbase_usage_exit(HBASE_PRINTENV_USAGE_STRING);

    argc -= optind;
    argv += optind;

    if (argc == 0) {
        for (ep = environ; *ep; ep++)
            printf("%s\n", *ep);
        return EXIT_SUCCESS;
    }

    len = strlen(*argv);
    for (ep = environ; *ep; ep++)
        if (!memcmp(*ep, *argv, len)) {
            cp = *ep + len;
            if (!*cp || *cp == '=') {
                printf("%s\n", *cp ? cp + 1 : cp);
                return EXIT_SUCCESS;
            }
        }

    return EXIT_FAILURE;
}

int main(int argc, char **argv) { return hbase_printenv(argc, argv); }
