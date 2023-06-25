#include <logger.h>
#include <Arduino.h>


Logger& Logger::Instance(){
    static Logger instance;
    return instance;
}


void Logger::Log(const char* message, LogLevel level){
    int msg_len = strlen(message);
    char buff[msg_len+12];
    sprintf(buff, "%s | %s\n", kLevelNames[level], message);
    Serial.print(buff);

    if(extern_output_)
        extern_output_(buff);
}


void Logger::AttachExternOutput(std::function<void(const char*)> callback_func){
    extern_output_ = callback_func;
}
