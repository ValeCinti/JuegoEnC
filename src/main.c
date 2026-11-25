#include <stdio.h>
#include "core/logs.h"

int main(){
    logs_types logs = LOG_INFO;
    log_register(logs,"hola");
    return 0;
}