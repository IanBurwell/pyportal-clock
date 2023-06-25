#include "sdcard_task.h"
#include <pins.h>
#include <logger.h>

void SDCardTask::Init(){
    // Init SD
    if (!sd_.begin(SD_CS_PIN, SPI_HALF_SPEED)) {
        Logger::Instance().Error("SD card not initialized");
        initialized_ = false;
        return;
    }

    // Create log file (incrementing log number)
    sd_.mkdir(LOG_DIR);
    char log_name[] = LOG_BASE_NAME;
    while(sd_.exists(log_name)){
        // Increment log number in the string by 1
        log_name[LOG_RIGHTMOST_DIGIT] = (log_name[LOG_RIGHTMOST_DIGIT]-'0'+1)%10+'0';
        if(log_name[LOG_RIGHTMOST_DIGIT] == '0'){
            log_name[LOG_RIGHTMOST_DIGIT-1] = (log_name[LOG_RIGHTMOST_DIGIT-1]-'0'+1)%10+'0';
            if(log_name[LOG_RIGHTMOST_DIGIT-1] == '0'){
                log_name[LOG_RIGHTMOST_DIGIT-2] = (log_name[LOG_RIGHTMOST_DIGIT-2]-'0'+1)%10+'0';
                if(log_name[LOG_RIGHTMOST_DIGIT-2] == '0'){
                    Logger::Instance().Error("Over 999 log files");
                    initialized_ = false;
                    return;
                }
            }
        }
    }
    log_file_.open(log_name, (O_CREAT | O_WRITE));

    // Attach logger
    Logger::Instance().AttachExternOutput(std::bind(&SDCardTask::Log, this, std::placeholders::_1));

    initialized_ = true;
}

void SDCardTask::Update(){
    Flush();
}

void SDCardTask::Flush(){
    if(log_buffer_size_ <= 0)
        return;

    // Track buffer largest size
    if(log_buffer_size_ > log_buffer_max_stored_)
        log_buffer_max_stored_ = log_buffer_size_;

    // Write buffer to file
    log_file_.write(log_buffer_, log_buffer_size_);
    log_file_.flush();
    log_buffer_size_ = 0;

}

void SDCardTask::Log(const char* str){
    // Fail if there is not enough buffer space
    int str_len = strlen(str);
    if(LOG_BUFFER_CAPACITY-log_buffer_size_ < str_len)
        return;

    // Fill buffer
    strcpy(log_buffer_+log_buffer_size_, str);
    log_buffer_size_ += str_len;
}