#ifndef LOGS_H
#define LOGS_H

typedef enum {
    LOG_INFO,
    LOG_WARNING,
    LOG_ERROR,
} logs_types;

void log_register(logs_types type,const char* message);

#endif