#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <pxbase/common.h>
#include <pxbase/nohup.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

static void mkfile(void)
{
    int fd;
    char path[PATH_MAX];
    char *filename;
    size_t len;

    filename = "nohup.out";

    fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
    if (fd >= 0)
        goto dupl;

    filename = getenv("HOME");
    if (filename != NULL) {
        len = strlen(filename);

        if (len + sizeof("/nohup.out") <= sizeof(path)) {
            strcpy(path, filename);
            strcat(path, "/");
            strcat(path, "nohup.out");
            filename = path;
            fd = open(filename, O_WRONLY | O_CREAT | O_APPEND,
                      S_IRUSR | S_IWUSR);
            if (fd >= 0)
                goto dupl;
        }
    }

    fprintf(stderr, "nohup: cannot open a 'nohup.out' file\n");
    exit(EXIT_FAILURE);

dupl:
    if (dup2(fd, STDOUT_FILENO) == -1) {
        perror("nohup");
        exit(EXIT_FAILURE);
    }
    fprintf(stderr, "sending output to %s\n", filename);
    if (fd != STDOUT_FILENO)
        close(fd);
}
int pxbase_nohup(int argc, char **argv)
{
    if (argc < 2)
        pxbase_usage_exit(PXBASE_NOHUP_USAGE_STRING);

    if (isatty(STDOUT_FILENO))
        mkfile();

    if (isatty(STDERR_FILENO) && dup2(STDOUT_FILENO, STDERR_FILENO) == -1) {
        perror("nohup");
        return EXIT_FAILURE;
    }

    if (signal(SIGHUP, SIG_IGN) == SIG_ERR) {
        perror("nohup");
        return EXIT_FAILURE;
    }

    if (signal(SIGQUIT, SIG_IGN) == SIG_ERR) {
        perror("nohup");
        return EXIT_FAILURE;
    }

    execvp(argv[1], &argv[1]);
    fprintf(stderr, "nohup: %s: %s\n", argv[1], strerror(errno));
    return EXIT_FAILURE;
}

#ifndef PXBASE_MULTICALL

int main(int argc, char **argv) { return pxbase_nohup(argc, argv); }

#endif
