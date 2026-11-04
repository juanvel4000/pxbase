#include <errno.h>
#include <fcntl.h>
#include <pxbase/common.h>
#include <pxbase/mktemp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

#define MAX_TRIES 100

static const char charset[] =
    "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
static unsigned long state;

static void seed(void)
{
    int stackvar;

    state = (unsigned long)time(NULL) ^ ((unsigned long)getpid() << 16) ^
            (unsigned long)&stackvar;
}

static void fill(char *x, size_t n)
{
    size_t i;

    for (i = 0; i < n; i++) {
        state = state * 1103515245UL + 12345UL;
        x[i] = charset[(state >> 16) % 62];
    }
}

int pxbase_mktemp(int argc, char **argv)
{
    int opt;
    int isdir;
    int rel;
    const char *dir;
    const char *template;
    char *buf;
    char *end;
    char *x;
    size_t n;
    int tries;
    int fd;

    isdir = 0;
    rel = 0;
    dir = NULL;

    while ((opt = getopt(argc, argv, "dtp:")) != -1) {
        switch (opt) {
        case 'd':
            isdir = 1;
            break;
        case 't':
            rel = 1;
            break;
        case 'p':
            dir = optarg;
            break;
        default:
            pxbase_usage_exit(PXBASE_MKTEMP_USAGE_STRING);
        }
    }

    if (optind < argc) {
        template = argv[optind];
    } else {
        template = "tmp.XXXXXXXXXX";
        rel = 1;
    }

    if (dir == NULL && rel) {
        dir = getenv("TMPDIR");
        if (dir == NULL || *dir == '\0')
            dir = "/tmp";
    }

    if (dir != NULL) {
        buf = malloc(strlen(dir) + strlen(template) + 2);
        if (buf == NULL) {
            perror("mktemp");
            return EXIT_FAILURE;
        }
        sprintf(buf, "%s/%s", dir, template);
    } else {
        buf = malloc(strlen(template) + 1);
        if (buf == NULL) {
            perror("mktemp");
            return EXIT_FAILURE;
        }
        strcpy(buf, template);
    }

    end = buf + strlen(buf);
    x = end;
    while (x > buf && x[-1] == 'X')
        x--;
    n = (size_t)(end - x);
    if (n < 3) {
        fprintf(stderr, "mktemp: too few X's in template: %s\n", template);
        return EXIT_FAILURE;
    }

    seed();
    for (tries = 0; tries < MAX_TRIES; tries++) {
        fill(x, n);
        if (isdir) {
            if (mkdir(buf, 0700) == 0)
                break;
        } else {
            fd = open(buf, O_RDWR | O_CREAT | O_EXCL, 0600);
            if (fd >= 0) {
                close(fd);
                break;
            }
        }
        if (errno != EEXIST) {
            perror(buf);
            return EXIT_FAILURE;
        }
    }
    if (tries == MAX_TRIES) {
        fprintf(stderr, "mktemp: failed to create a unique name\n");
        return EXIT_FAILURE;
    }

    puts(buf);
    return EXIT_SUCCESS;

    return EXIT_FAILURE;
}

#ifndef PXBASE_MULTICALL

int main(int argc, char **argv) { return pxbase_mktemp(argc, argv); }
#endif
