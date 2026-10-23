#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <pxbase/common.h>
#include <pxbase/ln.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

static int linkf(const char *target, const char *src, int symbolic, int follow)
{
    if (symbolic == 1) {
        return symlink(target, src);
    } else {
        return linkat(AT_FDCWD, target, AT_FDCWD, src,
                      follow == 1 ? AT_SYMLINK_FOLLOW : 0);
    }
}

static int do_link(const char *target, const char *src, int isdir, int force,
                   int symbolic, int follow)
{
    struct stat st;
    struct stat st2;
    int exists;
    const char *p;
    char path[PATH_MAX];
    int n;

    if (symbolic == 0) {
        if ((follow ? stat(target, &st) : lstat(target, &st)) != 0) {
            fprintf(stderr, "ln: %s: %s\n", target, strerror(errno));
            return EXIT_FAILURE;
        }

        if (S_ISDIR(st.st_mode) != 0) {
            fprintf(stderr, "ln: %s: is a directory\n", target);
            return EXIT_FAILURE;
        }
    }

    exists = lstat(src, &st) == 0;
    if (isdir == 1 || (stat(src, &st2) == 0 && S_ISDIR(st2.st_mode))) {
        p = strrchr(target, '/');
        if (p == NULL) {
            p = target;
        } else {
            ++p;
        }

        n = snprintf(path, sizeof(path), "%s/%s", src, p);
        if (n < 0 || (size_t)n >= sizeof(path)) {
            fprintf(stderr, "ln: %s: name too long\n", src);
            return EXIT_FAILURE;
        }
    }

    src = path;
    exists = lstat(src, &st) == 0;

    if (symbolic == 0 && exists != 0 &&
        (follow ? stat(target, &st2) : lstat(target, &st2)) == 0 &&
        st.st_dev == st2.st_dev && st.st_ino == st2.st_ino) {
        fprintf(stderr, "ln: %s: %s: same file\n", src, target);
        return EXIT_FAILURE;
    }

    if ((force == 1 && exists != 0 && unlink(src) != 0) ||
        linkf(target, src, symbolic, follow)) {
        fprintf(stderr, "ln: %s: %s\n", src, strerror(errno));
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

int pxbase_ln(int argc, char **argv)
{
    struct stat st;
    int opt;
    int ret;
    const char *srcdir;
    int force;
    int symbolic;
    int follow;

    force = 0;
    symbolic = 0;
    follow = 0;

    while ((opt = getopt(argc, argv, "fsLP")) != -1) {
        switch (opt) {
        case 'f':
            force = 1;
            break;
        case 's':
            symbolic = 1;
            break;
        case 'P':
            follow = 0;
            break;
        case 'L':
            follow = 1;
            break;
        case '?':
            pxbase_usage_exit(PXBASE_LN_USAGE_STRING);
        }
    }

    if (argc == optind)
        pxbase_usage_exit(PXBASE_LN_USAGE_STRING);

    argv += optind;
    argc -= optind;

    switch (argc) {
    case 1:
        return do_link(argv[0], ".", 1, force, symbolic, follow);
    case 2:
        return do_link(argv[0], argv[1], 0, force, symbolic, follow);
    }

    srcdir = argv[argc - 1];
    if (stat(srcdir, &st) != 0) {
        fprintf(stderr, "ln: %s: %s\n", srcdir, strerror(errno));
        return EXIT_FAILURE;
    }

    if (!S_ISDIR(st.st_mode))
        pxbase_usage_exit(PXBASE_LN_USAGE_STRING);

    for (ret = 0; *argv != srcdir; ++argv)
        ret |= do_link(*argv, srcdir, 1, force, symbolic, follow);

    return ret;
}

#ifndef PXBASE_MULTICALL

int main(int argc, char **argv) { return pxbase_ln(argc, argv); }

#endif
