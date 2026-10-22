#include <errno.h>
#include <fcntl.h>
#include <pxbase/common.h>
#include <pxbase/touch.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

static int touch_one(const char *file, int a, int m, int c)
{
    int fd;
    struct timespec ts[2];

    ts[0].tv_sec = 0;
    ts[0].tv_nsec = a ? UTIME_NOW : UTIME_OMIT;
    ts[1].tv_sec = 0;
    ts[1].tv_nsec = m ? UTIME_NOW : UTIME_OMIT;

    if (utimensat(AT_FDCWD, file, ts, 0) != 0) {
        if (errno != ENOENT) {
            return EXIT_FAILURE;
        }

        if (c)
            return EXIT_SUCCESS;

        fd = open(file, O_WRONLY | O_CREAT, 0666);
        if (fd == -1) {
            perror(file);
            return EXIT_FAILURE;
        }
        close(fd);
    }

    return EXIT_SUCCESS;
}

int pxbase_touch(int argc, char **argv)
{
    int opt;

    int a;
    int m;
    int c;
    int i;
    int ret;

    a = 0;
    m = 0;
    c = 0;
    ret = EXIT_SUCCESS;

    while ((opt = getopt(argc, argv, "amc")) != -1) {
        switch (opt) {
        case 'a':
            a = 1;
            break;
        case 'm':
            m = 1;
            break;
        case 'c':
            c = 1;
            break;
        case '?':
            pxbase_usage_exit(PXBASE_TOUCH_USAGE_STRING);
        }
    }

    if (!a && !m) {
        a = 1;
        m = 1;
    }

    if (optind == argc)
        pxbase_usage_exit(PXBASE_TOUCH_USAGE_STRING);

    for (i = optind; i < argc; i++)
        if (touch_one(argv[i], a, m, c) != 0)
            ret = EXIT_FAILURE;

    return ret;
}

int main(int argc, char **argv) { return pxbase_touch(argc, argv); }
