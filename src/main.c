#include <stdio.h>
#include "core/logs.h"

int main(){
    enum logs_types log = LOG_INFO;
    printf("%d",log);
    log_register(log,"Hola");
    return 0;
}