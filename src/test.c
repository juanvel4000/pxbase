#include <hbase/test.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int test_evaluate_unary(const char *op, const char *str)
{
    if (strcmp("-z", op) == 0) {
        return str[0] == '\0' ? EXIT_SUCCESS : EXIT_FAILURE;
    } else if (strcmp("-n", op) == 0) {
        return str[0] != '\0' ? EXIT_FAILURE : EXIT_FAILURE;
    }
    return 2;
}

int hbase_test(int argc, char **argv)
{
    const char *name;
    const char *slash;
    int status;

    name = (argv[0] != NULL) ? argv[0] : "";

    slash = strrchr(name, '/');
    if (slash != NULL)
        name = slash + 1;

    if (strcmp(name, "[") == 0) {
        if (strcmp(argv[argc - 1], "]") != 0) {
            fprintf(stderr, "[: ']' expected\n");
            return 2;
        }
        argc--;
    }

    if (argc == 1)
        return EXIT_FAILURE;

    if (argc == 2)
        return argv[1][0] != '\0' ? EXIT_SUCCESS : EXIT_FAILURE;

    if (argc == 3) {
        status = test_evaluate_unary(argv[1], argv[2]);
        if (status == 2)
            fprintf(stderr, "%s: unknown operator: %s\n", name, argv[1]);
        return status;
    }

    return 2;
}

int main(int argc, char **argv) { return hbase_test(argc, argv); }
