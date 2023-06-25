#pragma once
#include <task.h>
#include <SdFat.h>

#define LOG_BUFFER_CAPACITY 512
#define LOG_DIR "logs"
#define LOG_PREFIX "LOG_"
#define LOG_SUFFIX ".txt"
#define LOG_BASE_NAME LOG_DIR "/" LOG_PREFIX "000" LOG_SUFFIX
#define LOG_RIGHTMOST_DIGIT strlen(LOG_BASE_NAME)-strlen(LOG_SUFFIX)-1

class SDCardTask : public Task {
public:
    void Init() override;
    void Update() override;

    void Flush();
    void Log(const char* str);

    int buffer_max_stored(){return log_buffer_max_stored_;};
    SdFat& sd(){return sd_;};

private:
    SdFat sd_;
    File log_file_;
    bool initialized_ = false;

    int log_buffer_size_ = 0;
    int log_buffer_max_stored_ = 0;
    char log_buffer_[LOG_BUFFER_CAPACITY] = {0};

};


