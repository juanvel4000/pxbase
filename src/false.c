#include <pxbase/false.h>
#include <stdlib.h>

int pxbase_false(void) { return EXIT_FAILURE; }

int main(void) { return pxbase_false(); }
