#ifndef PXBASE_MKFIFO_H
#define PXBASE_MKFIFO_H
#define PXBASE_MKFIFO_USAGE_STRING "mkfifo [-m mode] file ..."

#include <sys/types.h>

int pxbase_mkfifo(int argc, char **argv);
int parse_mode(const char *s, mode_t *out);

#endif /* PXBASE_MKFIFO_H */
