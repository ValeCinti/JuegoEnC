#ifndef LOGS_H
#define LOGS_H

typedef enum {
    FC_LOG_INFO,
    FC_LOG_WARNING,
    FC_LOG_ERROR,
} logLevel;

void log_register(logLevel type,const char* message);

#endif