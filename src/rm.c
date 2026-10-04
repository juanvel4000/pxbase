#include <errno.h>
#include <hbase/common.h>
#include <hbase/rm.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

static int confirm(const char *path, const char *message)
{
    char buf[8];
    int c;

    fprintf(stderr, message, path);
    if (fgets(buf, sizeof(buf), stdin) == NULL)
        return 0;

    if (strchr(buf, '\n') == NULL) {
        while ((c = getchar()) != '\n' && c != EOF)
            ;
    }

    switch (buf[0]) {
    case 'y':
    case 'Y':
        return 1;
    default:
        return 0;
    }
}

int hbase_rm(int argc, char **argv)
{
    int opt;
    int status;
    int force;
    int interactive;
    int rm_hier;
    int i;
    struct stat st;

    rm_hier = 0;
    force = 0;
    interactive = 0;
    status = EXIT_SUCCESS;

    while ((opt = getopt(argc, argv, "fiRr")) != -1) {
        switch (opt) {
        case 'f':
            force = 1;
            interactive = 0;
            break;
        case 'i':
            interactive = 1;
            force = 0;
            break;
        case 'r':
        case 'R':
            rm_hier = 1;
            break;

        case '?':
            hbase_usage_exit(USAGE_STRING);
        }
    }

    (void)rm_hier;
    if (optind == argc) {
        if (force)
            return EXIT_SUCCESS;
        hbase_usage_exit(USAGE_STRING);
    }

    for (i = optind; i < argc; i++) {
        if (lstat(argv[i], &st) != 0) {
            if (force && errno == ENOENT)
                continue;
            perror(argv[i]);
            status = EXIT_FAILURE;
            continue;
        }

        if (S_ISDIR(st.st_mode)) {
            fprintf(stderr, "rm: %s: is a directory\n", argv[i]);
            status = EXIT_FAILURE;
            continue;
        }

        if (interactive && !confirm(argv[i], "rm: remove '%s'? ")) {
            continue;
        } else if (!force) {
            if (isatty(STDIN_FILENO) && !S_ISLNK(st.st_mode) &&
                access(argv[i], W_OK) != 0) {
                if (!confirm(argv[i], "rm: remove write-protected file '%s'? "))
                    continue;
            }
        }
        if (unlink(argv[i]) != 0) {
            perror(argv[i]);
            status = EXIT_FAILURE;
        }
    }
    return status;
}

int main(int argc, char **argv) { return hbase_rm(argc, argv); }
