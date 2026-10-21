#include <dirent.h>
#include <errno.h>
#include <grp.h>
#include <hbase/common.h>
#include <hbase/ls.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

static int cmp_names(const void *a, const void *b)
{
    return strcmp(*(char *const *)a, *(char *const *)b);
}

static void print_time(time_t t)
{
    struct tm *tm;
    time_t now;
    char buf[32];

    now = time(NULL);
    tm = localtime(&t);

    if (t > now - 15552000 && t < now + 86400) {
        strftime(buf, sizeof buf, "%b %d %H:%M", tm);
    } else {
        strftime(buf, sizeof buf, "%b %d %Y", tm);
    }

    printf("%s", buf);
}

static void print_owner_and_group(struct stat st)
{
    struct passwd *pw;
    struct group *gr;
    gr = getgrgid(st.st_gid);
    pw = getpwuid(st.st_uid);

    if (pw != NULL) {
        printf("%s ", pw->pw_name);
    } else {
        printf("%d ", st.st_uid);
    }

    if (gr != NULL) {
        printf("%s", gr->gr_name);
    } else {
        printf("%d", st.st_gid);
    }
}

static void print_permissions(struct stat st)
{
    if (S_ISLNK(st.st_mode))
        putchar('l');
    else if (S_ISDIR(st.st_mode))
        putchar('d');
    else
        putchar('-');

    putchar((st.st_mode & S_IRUSR) ? 'r' : '-');
    putchar((st.st_mode & S_IWUSR) ? 'w' : '-');
    putchar((st.st_mode & S_IXUSR) ? 'x' : '-');

    putchar((st.st_mode & S_IRGRP) ? 'r' : '-');
    putchar((st.st_mode & S_IWGRP) ? 'w' : '-');
    putchar((st.st_mode & S_IXGRP) ? 'x' : '-');

    putchar((st.st_mode & S_IROTH) ? 'r' : '-');
    putchar((st.st_mode & S_IWOTH) ? 'w' : '-');
    putchar((st.st_mode & S_IXOTH) ? 'x' : '-');
}

int ls_dir(const char *path, int include_dotfiles, int show_names,
           int long_format, int single_column)
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
    struct stat st;
    char *full_path;
    size_t path_len;
    size_t name_len;

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
        if (i > 0 && !single_column && !long_format)
            putchar(' ');
        if (long_format) {
            path_len = strlen(path);
            name_len = strlen(names[i]);
            full_path = malloc(path_len + name_len + 2);

            if (full_path == NULL) {
                perror("malloc failed");
                goto fail;
            }

            if (path_len > 0 && path[path_len - 1] == '/') {
                sprintf(full_path, "%s%s", path, names[i]);
            } else {
                sprintf(full_path, "%s/%s", path, names[i]);
            }

            if (lstat(full_path, &st) == -1) {
                perror("lstat");
                free(full_path);
                continue;
            }

            print_permissions(st);
            printf(" %lu ", (unsigned long)st.st_nlink);
            print_owner_and_group(st);
            printf(" %ld ", (long)st.st_size);
            print_time(st.st_mtim.tv_sec);
            printf(" %s\n", names[i]);

            free(full_path);
        } else {
            printf("%s", names[i]);
            if (single_column)
                putchar('\n');
        }
    }

    if (!single_column && !long_format)
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
    int long_format;
    int single_column;

    long_format = 0;
    single_column = 0;
    include_dotfiles = 0;
    show_names = 0;
    ret = EXIT_SUCCESS;

    while ((opt = getopt(argc, argv, "al1")) != -1) {
        switch (opt) {
        case 'a':
            include_dotfiles = 1;
            break;
        case 'l':
            long_format = 1;
            break;
        case '1':
            single_column = 1;
            break;
        case '?':
            hbase_usage_exit(HBASE_LS_USAGE_STRING);
        }
    }

    if (optind == argc)
        ret = ls_dir(".", include_dotfiles, 0, long_format, single_column);
    else {
        if (argc - optind > 1)
            show_names = 1;
        for (i = optind; i < argc; i++) {
            if (ls_dir(argv[i], include_dotfiles, show_names, long_format,
                       single_column) != EXIT_SUCCESS)
                ret = EXIT_FAILURE;
        }
    }

    return ret;
}

int main(int argc, char **argv) { return hbase_ls(argc, argv); }
