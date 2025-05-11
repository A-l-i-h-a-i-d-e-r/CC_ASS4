#include <stdio.h>
#include "utils.h"

void debug_log(const char *msg, const char *file, int line) {
    fprintf(stderr, "[DEBUG %s:%d] %s\n", file, line, msg);
}