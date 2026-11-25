#include <stdio.h>
#include "logs.h"

void log_register( logs_types type, const char* message){
    switch(type){
        case LOG_INFO:
            printf("LOG INFO, %s", message);
        break;
    }

}