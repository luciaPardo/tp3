#include "Exception.h"
#include <cstring>
#include <errno.h>
#include <cstdarg>
#include <cstdio>

#define MAX_ERR 256

Exception::Exception(const char* format, ...) noexcept {
   va_list args;
   va_start(args, format);
   vsnprintf(msg_error, MAX_ERR, format, args);
   va_end(args);
}


const char* Exception::what() const noexcept {
    return msg_error;
}
