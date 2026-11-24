
enum logs_types{
    LOG_INFO,
    LOG_WARNING,
    LOG_ERROR,
};

void log_register(enum logs_types type, char message){
    printf("%d %s",type, message);
}