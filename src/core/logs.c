#include <stdio.h>
#include "logs.h"

void log_register(logLevel type, const char* message) {
    switch (type) {
        case SY_LOG_INFO:
            printf("[INFO] %s\n", message);
            break;
        case SY_LOG_WARNING:
            printf("[WARNING] %s\n", message); 
            break;
        case SY_LOG_ERROR:
            fprintf(stderr, "[ERROR] %s\n", message);
            break;
        default:
            fprintf(stderr, "[LOG ?] %s\n", message);
            break;
    }
}