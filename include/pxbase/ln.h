#ifndef PXBASE_LN_H
#define PXBASE_LN_H
#define PXBASE_LN_USAGE_STRING                                                 \
    "ln [-fs] [-L|-P] target [linkname]\n"                                     \
    "       ln [-fs] [-L|-P] target ... directory"

int pxbase_ln(int argc, char **argv);

#endif /* PXBASE_LN_H */
