#include <pwd.h>
#include <pxbase/common.h>
#include <pxbase/whoami.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int pxbase_whoami(int argc, char **argv)
{
    uid_t uid;
    struct passwd *pwd;

    (void)argc;
    (void)argv;

    uid = getuid();
    pwd = getpwuid(uid);

    if (pwd && pwd->pw_name) {
        printf("%s\n", pwd->pw_name);
    } else {
        printf("%u\n", (unsigned int)uid);
    }

    return EXIT_SUCCESS;
}

#ifndef PXBASE_MULTICALL

int main(int argc, char **argv) { return pxbase_whoami(argc, argv); }

#endif
