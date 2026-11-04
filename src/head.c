#include <errno.h>
#include <limits.h>
#include <pxbase/common.h>
#include <pxbase/head.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static void head(FILE *fp, int num)
{
    int chr;

    while (num--) {
        while ((chr = getc(fp)) != EOF) {
            if (putchar(chr) == EOF) {
                fprintf(stderr, "head: stdout: %s\n", strerror(errno));
                return;
            }

            if (chr == '\n')
                break;
        }
    }
}

int pxbase_head(int argc, char **argv)
{
    int opt;
    int num;
    int first;
    char *end;
    FILE *fp;

    num = 10;

    while ((opt = getopt(argc, argv, "n:")) != -1) {
        switch (opt) {
        case 'n':
            num = (int)strtol(optarg, &end, 10);
            if (*end || num <= 0) {
                fprintf(stderr, "head: invalid line number: '%s'\n", optarg);
                return EXIT_FAILURE;
            }

            break;
        default:
            pxbase_usage_exit(PXBASE_HEAD_USAGE_STRING);
        }
    }

    if (argc == optind) {
        head(stdin, num);
    } else {
        for (first = 1; *argv; ++argv) {
            fp = fopen(*argv, "r");
            if (fp == NULL) {
                fprintf(stderr, "head: %s\n", strerror(errno));
                continue;
            }

            if (argc > 1) {
                printf("%s==> %s <==\n", first ? "" : "\n", *argv);
                first = 0;
            }

            head(fp, num);
            fclose(fp);
        }
    }

    return EXIT_SUCCESS;
}

#ifndef PXBASE_MULTICALL

int main(int argc, char **argv) { return pxbase_head(argc, argv); }

#endif
