#include <dirent.h>
#include <errno.h>
#include <hbase/common.h>
#include <hbase/ls.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static int cmp_names(const void *a, const void *b)
{
    return strcmp(*(char *const *)a, *(char *const *)b);
}

int ls_dir(const char *path, int include_dotfiles, int show_names)
{
    DIR *dir;
    struct dirent *entry;
    char **names;
    char **tmp;
    char *copy;
    size_t count;
    size_t capacity;
    size_t ncapacity;
    size_t i;

    capacity = 0;
    count = 0;
    names = 0;

    dir = opendir(path);
    if (!dir) {
        if (errno == ENOTDIR) {
            printf("%s\n", path);
            return EXIT_SUCCESS;
        }

        perror(path);
        return EXIT_FAILURE;
    }

    if (show_names)
        printf("\n%s:\n", path);

    while ((entry = readdir(dir)) != NULL) {
        if (include_dotfiles == 0)
            if (entry->d_name[0] == '.')
                continue;

        if (count == capacity) {
            ncapacity = capacity ? capacity * 2 : 8;

            tmp = realloc(names, ncapacity * sizeof *names);
            if (tmp == NULL)
                goto fail;

            names = tmp;
            capacity = ncapacity;
        }

        copy = malloc(strlen(entry->d_name) + 1);
        if (copy == NULL)
            goto fail;
        strcpy(copy, entry->d_name);
        names[count++] = copy;
    }

    if (count > 1)
        qsort(names, count, sizeof(char *), cmp_names);

    for (i = 0; i < count; i++) {
        if (i > 0)
            putchar(' ');
        printf("%s", names[i]);
    }

    putchar('\n');

    while (count > 0)
        free(names[--count]);
    free(names);
    closedir(dir);
    return EXIT_SUCCESS;

fail:
    perror(path);
    while (count > 0)
        free(names[--count]);
    free(names);
    closedir(dir);
    return EXIT_FAILURE;
}

int hbase_ls(int argc, char **argv)
{
    int opt;
    int include_dotfiles;
    int show_names;
    int ret;
    int i;

    include_dotfiles = 0;
    show_names = 0;
    ret = EXIT_SUCCESS;

    while ((opt = getopt(argc, argv, "a")) != -1) {
        switch (opt) {
        case 'a':
            include_dotfiles = 1;
            break;
        case '?':
            hbase_usage_exit(HBASE_LS_USAGE_STRING);
        }
    }

    if (optind == argc)
        ret = ls_dir(".", include_dotfiles, 0);
    else {
        if (argc - optind > 1)
            show_names = 1;
        for (i = optind; i < argc; i++) {
            if (ls_dir(argv[i], include_dotfiles, show_names) != EXIT_SUCCESS)
                ret = EXIT_FAILURE;
        }
    }

    return ret;
}

int main(int argc, char **argv) { return hbase_ls(argc, argv); }
