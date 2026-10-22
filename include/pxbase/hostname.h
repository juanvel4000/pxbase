#ifndef PXBASE_HOSTNAME_H
#define PXBASE_HOSTNAME_H
#define PXBASE_HOSTNAME_USAGE_STRING "hostname [name-of-host]"

#ifndef HOST_NAME_MAX
#define HOST_NAME_MAX 255
#endif

int pxbase_hostname(int argc, char **argv);

#endif /* PXBASE_HOSTNAME_H */
