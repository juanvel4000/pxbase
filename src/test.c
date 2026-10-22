#include <errno.h>
#include <pxbase/test.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define TEST_OK 0
#define TEST_ERR 1
#define TEST_SYN 2

static int parse_int(const char *s, long *out)
{
    char *end;

    errno = 0;
    *out = strtol(s, &end, 10);
    if (s[0] == '\0' || *end != '\0' || errno == ERANGE)
        return -1;
    return 0;
}

static int is_file_op(const char *op)
{
    static const char *ops[] = {"-e", "-f", "-d", "-s", "-r",
                                "-w", "-x", "-h", "-L", NULL};
    int i;

    for (i = 0; ops[i] != NULL; i++)
        if (strcmp(op, ops[i]) == 0)
            return 1;
    return 0;
}

static int test_evaluate_unary_fileop(const char *op, const char *item,
                                      const char *name)
{
    struct stat st;

    if (!is_file_op(op)) {
        fprintf(stderr, "%s: unknown operator: %s\n", name, op);
        return TEST_SYN;
    }

    if (strcmp(op, "-r") == 0)
        return access(item, R_OK) == 0 ? TEST_OK : TEST_ERR;

    if (strcmp(op, "-w") == 0)
        return access(item, W_OK) == 0 ? TEST_OK : TEST_ERR;

    if (strcmp(op, "-x") == 0)
        return access(item, X_OK) == 0 ? TEST_OK : TEST_ERR;

    if (strcmp(op, "-h") == 0 || strcmp(op, "-L") == 0)
        return (lstat(item, &st) == 0 && S_ISLNK(st.st_mode)) ? TEST_OK
                                                              : TEST_ERR;

    if (stat(item, &st) != 0)
        return TEST_ERR;

    if (strcmp("-e", op) == 0)
        return TEST_OK;

    if (strcmp("-f", op) == 0)
        return S_ISREG(st.st_mode) ? TEST_OK : TEST_ERR;

    if (strcmp("-d", op) == 0)
        return S_ISDIR(st.st_mode) ? TEST_OK : TEST_ERR;

    if (strcmp("-s", op) == 0)
        return st.st_size > 0 ? TEST_OK : TEST_ERR;

    fprintf(stderr, "%s: unknown operator: %s\n", name, op);
    return TEST_SYN;
}

static int test_evaluate_unary(const char *op, const char *item,
                               const char *name)
{
    if (strcmp("-z", op) == 0)
        return item[0] == '\0' ? TEST_OK : TEST_ERR;

    if (strcmp("-n", op) == 0)
        return item[0] != '\0' ? TEST_OK : TEST_ERR;

    return test_evaluate_unary_fileop(op, item, name);
}

static int test_evaluate_binary(const char *op, const char *item1,
                                const char *item2, const char *name)
{
    long litem1;
    long litem2;

    if (strcmp(op, "=") == 0) {
        if (strcmp(item1, item2) == 0)
            return TEST_OK;
        return TEST_ERR;
    }

    if (strcmp(op, "!=") == 0) {
        if (strcmp(item1, item2) == 0)
            return TEST_ERR;
        return TEST_OK;
    }

    if (parse_int(item1, &litem1) != 0 || parse_int(item2, &litem2) != 0) {
        fprintf(stderr, "%s: integer expression expected\n", name);
        return TEST_SYN;
    }

    if (strcmp(op, "-eq") == 0)
        return litem1 == litem2 ? TEST_OK : TEST_ERR;

    if (strcmp(op, "-ne") == 0)
        return litem1 != litem2 ? TEST_OK : TEST_ERR;

    if (strcmp(op, "-gt") == 0)
        return litem1 > litem2 ? TEST_OK : TEST_ERR;

    if (strcmp(op, "-ge") == 0)
        return litem1 >= litem2 ? TEST_OK : TEST_ERR;

    if (strcmp(op, "-lt") == 0)
        return litem1 < litem2 ? TEST_OK : TEST_ERR;

    if (strcmp(op, "-le") == 0)
        return litem1 <= litem2 ? TEST_OK : TEST_ERR;

    fprintf(stderr, "%s: unknown operator: %s\n", name, op);
    return TEST_SYN;
}

static int flip_results(int res)
{
    if (res == TEST_SYN)
        return TEST_SYN;
    return res == TEST_OK ? TEST_ERR : TEST_OK;
}

static int is_binary_op(const char *op)
{
    static const char *ops[] = {"=",   "!=",  "-eq", "-ne", "-gt",
                                "-ge", "-lt", "-le", NULL};

    int i;

    for (i = 0; ops[i] != NULL; i++)
        if (strcmp(op, ops[i]) == 0)
            return 1;
    return 0;
}

static int test_eval(int n, char **args, const char *name)
{
    switch (n) {
    case 0:
        return TEST_ERR;
    case 1:
        return args[0][0] != '\0' ? TEST_OK : TEST_ERR;
    case 2:
        if (strcmp(args[0], "!") == 0)
            return flip_results(test_eval(1, args + 1, name));
        return test_evaluate_unary(args[0], args[1], name);
    case 3:
        if (is_binary_op(args[1]) != 0)
            return test_evaluate_binary(args[1], args[0], args[2], name);

        if (strcmp(args[0], "!") == 0)
            return flip_results(test_eval(2, args + 1, name));

        fprintf(stderr, "%s: unknown operator: %s\n", name, args[1]);
        return TEST_SYN;
    case 4:
        if (strcmp(args[0], "!") == 0)
            return flip_results(test_eval(3, args + 1, name));
        /* falls through */
    default:
        fprintf(stderr, "%s: too many arguments\n", name);
        return TEST_SYN;
    }
}

int pxbase_test(int argc, char **argv)
{
    const char *name;
    const char *slash;

    name = (argv[0] != NULL) ? argv[0] : "";

    slash = strrchr(name, '/');
    if (slash != NULL)
        name = slash + 1;

    if (strcmp(name, "[") == 0) {
        if (strcmp(argv[argc - 1], "]") != 0) {
            fprintf(stderr, "[: ']' expected\n");
            return TEST_SYN;
        }
        argc--;
    }

    return test_eval(argc - 1, argv + 1, name);
}

int main(int argc, char **argv) { return pxbase_test(argc, argv); }
