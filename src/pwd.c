#include <errno.h>
#include <pxbase/common.h>
#include <pxbase/pwd.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

static const char *pwd_getcwd(const char *cwd, int physical)
{
    const char *pwd;
    struct stat cst, pst;

    if (physical)
        return cwd;

    if (!(pwd = getenv("PWD")) || pwd[0] != '/' || stat(pwd, &pst) < 0)
        return cwd;
    if (stat(cwd, &cst) < 0) {
        fprintf(stderr, "pwd: stat %s: %s\n", cwd, strerror(errno));
        exit(EXIT_FAILURE);
    }

    return (pst.st_dev == cst.st_dev && pst.st_ino == cst.st_ino) ? pwd : cwd;
}

int pxbase_pwd(int argc, char **argv)
{
    int opt;
    char cwd[PATH_MAX];
    int physical = 0;

    if (!getcwd(cwd, sizeof(cwd))) {
        fprintf(stderr, "pwd: getcwd: %s\n", strerror(errno));
        return EXIT_FAILURE;
    }

    while ((opt = getopt(argc, argv, "LP")) != -1)
        switch (opt) {
        case 'L':
            physical = 0;
            break;
        case 'P':
            physical = 1;
            break;
        case '?':
            pxbase_usage_exit(PXBASE_PWD_USAGE_STRING);
        }
    if (optind < argc)
        pxbase_usage_exit(PXBASE_PWD_USAGE_STRING);

    printf("%s\n", pwd_getcwd(cwd, physical));
    return EXIT_SUCCESS;
}

int main(int argc, char **argv) { return pxbase_pwd(argc, argv); }
