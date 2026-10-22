#include <errno.h>
#include <fcntl.h>
#include <pxbase/cat.h>
#include <pxbase/common.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static int copy_fd(int fd)
{
    char buf[4096];
    ssize_t n;
    ssize_t off;
    ssize_t w;

    while (1) {
        n = read(fd, buf, sizeof(buf));

        if (n == 0)
            break;

        if (n < 0) {
            if (errno == EINTR)
                continue;

            perror("cat");
            return 1;
        }

        off = 0;

        while (off < n) {
            w = write(STDOUT_FILENO, buf + off, n - off);
            if (w < 0) {
                if (errno == EINTR)
                    continue;

                perror("cat");
                return 1;
            }

            off += w;
        }
    }

    return 0;
}

int pxbase_cat(int argc, char **argv)
{
    int opt;
    int status;
    int fd;
    int i;

    status = EXIT_SUCCESS;

    while ((opt = getopt(argc, argv, "u")) != -1) {
        switch (opt) {
        case 'u':
            break;
        case '?':
            pxbase_usage_exit(PXBASE_CAT_USAGE_STRING);
        }
    }

    if (optind == argc)
        return copy_fd(STDIN_FILENO);

    for (i = optind; i < argc; i++) {
        if (strcmp(argv[i], "-") == 0) {
            fd = STDIN_FILENO;
        } else {
            fd = open(argv[i], O_RDONLY);
            if (fd < 0) {
                perror(argv[i]);
                status = EXIT_FAILURE;
                continue;
            }
        }

        if (copy_fd(fd) != 0)
            status = EXIT_FAILURE;

        if (fd != STDIN_FILENO)
            close(fd);
    }

    return status;
}

#ifndef PXBASE_MULTICALL

int main(int argc, char **argv) { return pxbase_cat(argc, argv); }

#endif
