#pragma once


static constexpr const char* kLevelNames[] = {"ERROR", "WARN ", "INFO ", "DEBUG"};

class Logger {
public:
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;
    static Logger& Instance();

    enum LogLevel {
        kError   = 0,
        kWarning = 1,
        kInfo    = 2,
        kDebug   = 3
    };
    

    void Debug(const char* message){Log(message, LogLevel::kDebug);};
    void Info(const char* message){Log(message, LogLevel::kInfo);};
    void Warning(const char* message){Log(message, LogLevel::kWarning);};
    void Error(const char* message){Log(message, LogLevel::kError);};

    void Log(const char* message, LogLevel level);

private:
    LogLevel log_level_ = LogLevel::kInfo;
    Logger() = default;
    ~Logger() = default;
};

