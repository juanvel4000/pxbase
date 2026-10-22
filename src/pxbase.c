#include <libgen.h>
#include <pxbase/basename.h>
#include <pxbase/cat.h>
#include <pxbase/common.h>
#include <pxbase/dirname.h>
#include <pxbase/echo.h>
#include <pxbase/env.h>
#include <pxbase/false.h>
#include <pxbase/hostname.h>
#include <pxbase/logname.h>
#include <pxbase/ls.h>
#include <pxbase/mkdir.h>
#include <pxbase/nohup.h>
#include <pxbase/printenv.h>
#include <pxbase/pwd.h>
#include <pxbase/rm.h>
#include <pxbase/rmdir.h>
#include <pxbase/sleep.h>
#include <pxbase/sync.h>
#include <pxbase/test.h>
#include <pxbase/touch.h>
#include <pxbase/true.h>
#include <pxbase/tty.h>
#include <pxbase/uname.h>
#include <pxbase/yes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct applet {
    const char *name;
    int (*fn)(int, char **);
};

static const struct applet applets[] = {{"[", pxbase_test},
                                        {"basename", pxbase_basename},
                                        {"cat", pxbase_cat},
                                        {"test", pxbase_test},
                                        {"dirname", pxbase_dirname},
                                        {"echo", pxbase_echo},
                                        {"env", pxbase_env},
                                        {"false", pxbase_false},
                                        {"hostname", pxbase_hostname},
                                        {"logname", pxbase_logname},
                                        {"ls", pxbase_ls},
                                        {"mkdir", pxbase_mkdir},
                                        {"nohup", pxbase_nohup},
                                        {"printenv", pxbase_printenv},
                                        {"pwd", pxbase_pwd},
                                        {"rm", pxbase_rm},
                                        {"rmdir", pxbase_rmdir},
                                        {"sleep", pxbase_sleep},
                                        {"sync", pxbase_sync},
                                        {"touch", pxbase_touch},
                                        {"true", pxbase_true},
                                        {"tty", pxbase_tty},
                                        {"uname", pxbase_uname},
                                        {"yes", pxbase_yes},
                                        {NULL, NULL}};

static int run_applet(const char *name, int argc, char **argv)
{
    const struct applet *e;

    for (e = applets; e->name != NULL; e++)
        if (strcmp(e->name, name) == 0)
            return e->fn(argc, argv);

    return -2;
}

int main(int argc, char **argv)
{
    int res;
    char *name;
    const struct applet *e;

    name = (basename)(argv[0]);
    if (strcmp(name, "pxbase") == 0) {
        if (argc < 2) {
            fprintf(stderr, "usage: pxbase applet\n");
            fprintf(stderr, "try 'pxbase -l' for a list of applets\n");
            return EXIT_FAILURE;
        }

        if (argc == 2 && strcmp(argv[1], "-l") == 0) {
            for (e = applets; e->name != NULL; e++)
                printf("%s\n", e->name);
            return EXIT_SUCCESS;
        }

        argv++;
        argc--;
        name = (basename)(argv[0]);
    }

    res = run_applet(name, argc, argv);
    if (res == -2) {
        fprintf(stderr, "pxbase: %s: applet not found\n", name);
        return EXIT_FAILURE;
    }

    return res;
}
