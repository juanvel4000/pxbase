#include <pxbase/common.h>
#include <pxbase/uname.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/utsname.h>
#include <unistd.h>

static int first = 1;

static void field(const char *s)
{
    if (!first)
        putchar(' ');
    fputs(s, stdout);
    first = 0;
}

int pxbase_uname(int argc, char **argv)
{
    int s;
    int v;
    int n;
    int m;
    int r;
    int opt;
    struct utsname u;

    s = 0;
    v = 0;
    n = 0;
    m = 0;
    r = 0;

    while ((opt = getopt(argc, argv, "asnrvm")) != -1) {
        switch (opt) {
        case 'a':
            s = 1;
            v = 1;
            n = 1;
            m = 1;
            r = 1;
            break;
        case 'v':
            v = 1;
            break;
        case 'n':
            n = 1;
            break;
        case 'm':
            m = 1;
            break;
        case 'r':
            r = 1;
            break;
        case 's':
            s = 1;
            break;
        case '?':
            pxbase_usage_exit(PXBASE_UNAME_USAGE_STRING);
        }
    }

    if (!s && !v && !n && !m && !r)
        s = 1;

    if (uname(&u) != 0) {
        perror("uname");
        return EXIT_FAILURE;
    }

    if (s)
        field(u.sysname);
    if (n)
        field(u.nodename);
    if (r)
        field(u.release);
    if (v)
        field(u.version);
    if (m)
        field(u.machine);

    printf("\n");

    return EXIT_SUCCESS;
}

#ifndef PXBASE_MULTICALL

int main(int argc, char **argv) { return pxbase_uname(argc, argv); }

#endif
