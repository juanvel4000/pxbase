#ifndef HBASE_HOSTNAME_H
#define HBASE_HOSTNAME_H
#define HBASE_HOSTNAME_USAGE_STRING "hostname [name-of-host]"

#ifndef HOST_NAME_MAX
#define HOST_NAME_MAX 255
#endif

int hbase_hostname(int argc, char **argv);

#endif /* HBASE_HOSTNAME_H */
