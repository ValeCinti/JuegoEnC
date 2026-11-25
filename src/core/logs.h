#ifndef LOGS_H
#define LOGS_H

#include <stdio.h>

typedef enum {
    FC_LOG_INFO,
    FC_LOG_WARN,
    FC_LOG_ERROR
} LogLevel;

static inline void log_register(LogLevel type, const char *message) {
    printf("[%d] %s\n", type, message);
}

#endif