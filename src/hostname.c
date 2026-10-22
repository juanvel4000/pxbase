#include <hbase/common.h>
#include <hbase/hostname.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int hbase_hostname(int argc, char **argv)
{
    char hostname[HOST_NAME_MAX + 1];

    if (argc == 1) {
        if (gethostname(hostname, sizeof hostname) == -1) {
            perror("hostname");
            return EXIT_FAILURE;
        }

        hostname[HOST_NAME_MAX] = '\0';
        printf("%s\n", hostname);
    } else if (argc == 2) {
        if (strlen(argv[1]) > HOST_NAME_MAX) {
            fprintf(stderr, "hostname: name too long\n");
            return EXIT_FAILURE;
        }

        if (sethostname(argv[1], strlen(argv[1])) == -1) {
            perror("hostname");
            return EXIT_FAILURE;
        }
    } else {
        hbase_usage_exit(HBASE_HOSTNAME_USAGE_STRING);
    }

    return EXIT_SUCCESS;
}

int main(int argc, char **argv) { return hbase_hostname(argc, argv); }
