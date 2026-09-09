#include <hbase/false.h>
#include <stdlib.h>

int false(void) { return EXIT_FAILURE; }

int main(void) { return false(); }
