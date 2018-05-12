#include "err.h"
#include <windows.h>
#include <stdio.h>
#include <errno.h>

int err(int eval, const char *fmt, ...) {
   va_list ap;
   va_start(ap, fmt);
   fprintf(stderr, "htop: ");
   vfprintf(stderr, fmt, ap);
   fprintf(stderr, ": %s", strerror(errno));
   fputc('\n', stderr);
   va_end(ap);
   exit(eval);
}
