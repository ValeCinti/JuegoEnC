#ifndef LOGS_H
#define LOGS_H

typedef enum {
    SY_LOG_INFO,
    SY_LOG_WARNING,
    SY_LOG_ERROR,
} logLevel;

void log_register(logLevel type,const char* message);

#endif