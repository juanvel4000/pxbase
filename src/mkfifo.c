#include <errno.h>
#include <pxbase/common.h>
#include <pxbase/mkfifo.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int pxbase_mkfifo(int argc, char **argv)
{
    int opt;
    mode_t mode;
    int i;
    int ret;

    mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;
    ret = EXIT_SUCCESS;

    while ((opt = getopt(argc, argv, "m:")) != -1) {
        switch (opt) {
        case 'm':
            if (parse_mode(optarg, &mode) != 0) {
                fprintf(stderr, "mkfifo: invalid mode: %s\n", optarg);
                return EXIT_FAILURE;
            }

            break;
        default:
            pxbase_usage_exit(PXBASE_MKFIFO_USAGE_STRING);
        }
    }

    if (optind == argc)
        pxbase_usage_exit(PXBASE_MKFIFO_USAGE_STRING);

    argc -= optind;
    argv += optind;

    for (i = 0; argc > i; i++) {
        if (mkfifo(argv[i], mode) != 0) {
            fprintf(stderr, "mkfifo: %s: %s\n", argv[i], strerror(errno));
            ret = EXIT_FAILURE;
        }
    }

    return ret;
}
#ifndef PXBASE_MULTICALL

int main(int argc, char **argv) { return pxbase_mkfifo(argc, argv); }

#endif
