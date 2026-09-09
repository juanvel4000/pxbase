#include <hbase/false.h>
#include <stdlib.h>

int hfalse(void) { return EXIT_FAILURE; }

int main(void) { return hfalse(); }
