#include <dirent.h>
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

static int remove_one(const char *path, const struct stat st, int force,
                      int interactive)
{

    if (interactive && !confirm(path, "rm: remove '%s'? ")) {
        return 2;
    } else if (!force) {
        if (isatty(STDIN_FILENO) && !S_ISLNK(st.st_mode) &&
            access(path, W_OK) != 0) {
            if (!confirm(path, "rm: remove write-protected file '%s'? "))
                return 2;
        }
    }
    if (unlink(path) != 0) {
        perror(path);
        return 1;
    }

    return 0;
}

static int remove_tree(const char *path, int force, int interactive)
{
    char child[PATH_MAX];
    int status;
    DIR *d;
    int n;
    struct dirent *entry;
    struct stat st;
    int r;
    int skipped;

    skipped = 0;
    status = 0;

    if (interactive && !confirm(path, "rm: descend into directory '%s'? "))
        return 2;

    d = opendir(path);

    if (d == NULL) {
        perror("opendir");
        return 1;
    }

    while ((entry = readdir(d))) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        n = snprintf(child, sizeof(child), "%s/%s", path, entry->d_name);
        if (n < 0 || (size_t)n >= sizeof(child)) {
            errno = ENAMETOOLONG;
            perror(path);
            status = 1;
            continue;
        }

        if (lstat(child, &st) != 0) {
            if (force && errno == ENOENT)
                continue;

            perror("lstat");
            status = 1;
            continue;
        }

        r = S_ISDIR(st.st_mode) ? remove_tree(child, force, interactive)
                                : remove_one(child, st, force, interactive);

        if (r == 1) {
            status = 1;
        } else if (r == 2) {
            skipped = 1;
        }
    }

    closedir(d);
    if (status != 0)
        return 1;

    if (skipped)
        return 2;

    if (interactive && !confirm(path, "rm: remove directory '%s'? "))
        return 2;

    if (rmdir(path) != 0) {
        perror("rmdir");
        return 1;
    }

    return 0;
}

static int is_dot_or_dotdot(const char *path)
{
    size_t len;
    size_t start;
    size_t n;

    len = strlen(path);

    while (len > 0 && path[len - 1] == '/') {
        len--;
    }

    if (len == 0)
        return 1;

    start = len;

    while (start > 0 && path[start - 1] != '/') {
        start--;
    }

    n = len - start;

    if (n == 1 && path[start] == '.')
        return 1;

    if (n == 2 && path[start] == '.' && path[start + 1] == '.')
        return 1;

    return 0;
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
            hbase_usage_exit(HBASE_RM_USAGE_STRING);
        }
    }

    if (optind == argc) {
        if (force)
            return EXIT_SUCCESS;
        hbase_usage_exit(HBASE_RM_USAGE_STRING);
    }

    for (i = optind; i < argc; i++) {
        if (is_dot_or_dotdot(argv[i])) {
            fprintf(stderr, "rm: refusing to remove '.' or '..': %s\n",
                    argv[i]);
            status = EXIT_FAILURE;
            continue;
        }

        if (lstat(argv[i], &st) != 0) {
            if (force && errno == ENOENT)
                continue;
            perror(argv[i]);
            status = EXIT_FAILURE;
            continue;
        }

        if (S_ISDIR(st.st_mode)) {
            if (!rm_hier) {
                fprintf(stderr, "rm: %s: is a directory\n", argv[i]);
                status = EXIT_FAILURE;
                continue;
            } else {
                if (remove_tree(argv[i], force, interactive) == 1)
                    status = EXIT_FAILURE;
                continue;
            }
        }

        if (remove_one(argv[i], st, force, interactive) == 1)
            status = EXIT_FAILURE;
    }
    return status;
}

int main(int argc, char **argv) { return hbase_rm(argc, argv); }
