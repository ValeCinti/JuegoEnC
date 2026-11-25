#include <stdio.h>
#include "logs.h"

void log_register(logLevel type, const char *message) {
    switch (type) {
        case FC_LOG_INFO:
            printf("[INFO] %s\n", message);
            break;
        case FC_LOG_WARNING:
            printf("[WARNING] %s\n", message);
            break;
        case FC_LOG_ERROR:
            fprintf(stderr, "[ERROR] %s\n", message);
            break;
        default:
            fprintf(stderr, "[LOG ?] %s\n", message);
            break;
    }
}