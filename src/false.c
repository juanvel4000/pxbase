#include <hbase/false.h>
#include <stdlib.h>

int hbase_false(void) { return EXIT_FAILURE; }

int main(void) { return hbase_false(); }
