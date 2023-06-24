#include <logger.h>
#include <Arduino.h>

Logger& Logger::Instance(){
    static Logger instance;
    return instance;
}


void Logger::Log(const char* message, LogLevel level){
    // Note: printf is not arduino standard but is implemented by the SAMD core
    Serial.printf("%s | %s", kLevelNames[level], message);
    Serial.println();
}
