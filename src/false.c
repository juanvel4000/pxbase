#include <stdlib.h>

int false(void) { return EXIT_FAILURE; }

int main(int argc, char **argv) { return false(); }
