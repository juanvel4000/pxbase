#include <hbase/basename.h>
#include <hbase/common.h>
#include <libgen.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void remove_suffix(char *name, const char *suffix)
{
    size_t name_len;
    size_t suffix_len;

    if (suffix == NULL)
        return;

    name_len = strlen(name);
    suffix_len = strlen(suffix);

    if (suffix_len <= name_len &&
        strcmp(name + name_len - suffix_len, suffix) == 0) {
        name[name_len - suffix_len] = '\0';
    }
}

int hbase_basename(int argc, char **argv)
{
    char path[PATH_MAX];
    char *result;

    if (argc < 2 || argc > 3)
        hbase_usage_exit(USAGE_STRING);

    if (strlen(argv[1]) >= sizeof(path)) {
        fprintf(stderr, "basename: path too long\n");
        return EXIT_FAILURE;
    }

    strcpy(path, argv[1]);

    if (argc == 3) {
        char *base = basename(path);

        remove_suffix(base, argv[2]);
        printf("%s\n", base);
    } else if (argc == 2) {
        result = basename(path);
        printf("%s\n", result);
    }

    return EXIT_SUCCESS;
}

int main(int argc, char **argv)
{
    if (argc == 1)
        hbase_usage_exit(USAGE_STRING);

    return hbase_basename(argc, argv);
}
