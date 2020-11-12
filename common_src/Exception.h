#ifndef TP3_EXCEPTION_H
#define TP3_EXCEPTION_H
#include <sys/types.h>
#include <typeinfo>
#include <unistd.h>
#include <cstring>
#include <iostream>
#include <string>

#define MAX_ERR 256

class Exception : public std::exception {
private:
    char msg_error[MAX_ERR];
public:
    explicit Exception(const char* format, ...) noexcept;
    virtual const char* what() const noexcept;
    virtual ~Exception() noexcept {}
};


#endif
