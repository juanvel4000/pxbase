#include <hbase/basename.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void usage(void)
{
    fprintf(stderr, "usage: basename path [suffix]\n");
    exit(EXIT_FAILURE);
}
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

int get_basename(int argc, char **argv)
{
    char *result;

    if (argc < 2)
        usage();

    if (argc > 3)
        usage();

    if (argc == 3) {
        char *base = basename(argv[1]);

        remove_suffix(base, argv[2]);
        printf("%s\n", base);
    } else if (argc == 2) {
        result = basename(argv[1]);
        printf("%s\n", result);
    }

    return EXIT_SUCCESS;
}

int main(int argc, char **argv)
{
    if (argc == 1)
        usage();

    return get_basename(argc, argv);
}
