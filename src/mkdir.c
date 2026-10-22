#include <errno.h>
#include <pxbase/common.h>
#include <pxbase/mkdir.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

static int mkdir_p(const char *path, int has_mode, mode_t mode)
{
    char tmp[PATH_MAX];
    size_t len;
    char *p;
    struct stat st;
    int created;

    created = 0;

    strncpy(tmp, path, sizeof(tmp));
    tmp[sizeof(tmp) - 1] = '\0';

    len = strlen(tmp);
    if (len == 0)
        return -1;

    if (tmp[len - 1] == '/')
        tmp[len - 1] = '\0';

    for (p = tmp + 1; *p; p++) {
        if (*p == '/') {
            *p = '\0';
            if (mkdir(tmp, 0777) != 0) {
                if (errno != EEXIST)
                    return -1;
            }
            *p = '/';
        }
    }

    if (mkdir(tmp, 0777) == 0) {
        created = 1;
    } else {
        if (errno != EEXIST)
            return -1;

        if (stat(tmp, &st) != 0)
            return -1;

        if (!S_ISDIR(st.st_mode)) {
            errno = ENOTDIR;
            return -1;
        }
    }

    if (has_mode && created)
        if (chmod(tmp, mode) != 0)
            return -1;

    return 0;
}

static int parse_mode(const char *s, mode_t *out)
{
    char *end;
    long value;

    errno = 0;
    value = strtol(s, &end, 8);

    if (errno == ERANGE)
        return -1;

    if (end == s)
        return -1;

    if (*end != '\0')
        return -1;

    if (value < 0)
        return -1;

    if (value > 07777)
        return -1;

    *out = value;

    return 0;
}

int pxbase_mkdir(int argc, char **argv)
{
    int opt;
    int status;
    int p;
    mode_t mode;
    int has_mode;
    int i;

    mode = 0;
    p = 0;
    has_mode = 0;
    status = EXIT_SUCCESS;

    while ((opt = getopt(argc, argv, "pm:")) != -1) {
        switch (opt) {
        case 'p':
            p = 1;
            break;
        case 'm':
            has_mode = 1;
            if (parse_mode(optarg, &mode) != 0) {
                fprintf(stderr, "mkdir: invalid mode: %s\n", optarg);
                return EXIT_FAILURE;
            }
            break;
        case '?':
            pxbase_usage_exit(PXBASE_MKDIR_USAGE_STRING);
        }
    }

    if (optind == argc)
        pxbase_usage_exit(PXBASE_MKDIR_USAGE_STRING);

    for (i = optind; i < argc; i++) {
        if (p) {
            if (mkdir_p(argv[i], has_mode, mode) != 0) {
                perror(argv[i]);
                status = EXIT_FAILURE;
                continue;
            }
        } else {
            if (mkdir(argv[i], 0777) != 0) {
                perror(argv[i]);
                status = EXIT_FAILURE;
                continue;
            }

            if (has_mode) {
                if (chmod(argv[i], mode) != 0) {
                    perror(argv[i]);
                    status = EXIT_FAILURE;
                }
            }
        }
    }
    return status;
}

int main(int argc, char **argv) { return pxbase_mkdir(argc, argv); }
