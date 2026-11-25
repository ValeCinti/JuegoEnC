#include <stdio.h>
#include "logs.h"

void log_register( logLevel type, const char* message){
    switch(type){
        case FC_LOG_INFO:
            printf("[FC LOG INFO], %s", message);
        break;
    }

}