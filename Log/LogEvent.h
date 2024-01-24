#pragma

#include <sstream>
#include <string>
#include <memory>
#include <stdarg.h>
#include "LogLevel.h"
#include "Logger.h"


class LogEvent {
public:
    typedef std::shared_ptr<LogEvent> ptr;

    LogEvent(const std::string& loggerName, LogLevel::Level level, 
            const std::string fileName, uint64_t line, 
            uint64_t elapse, uint64_t threadId, uint64_t fiberId, 
            uint64_t time, const std::string& threadName);
    
    LogLevel::Level getLevel() const { return level_; }
    std::string getContent() const { return ss_.str(); }
    std::string getFilename() const { return filename_; }
    uint64_t getElapse() const { return elapse_; }
    uint64_t getLine() const { return line_; }
    uint64_t getThreadId() const { return threadId_; }
    uint64_t getFiberId() const { return fiberId_; }
    uint64_t getTime() const { return time_; }
    std::string getThreadname() const { return threadname_; }
    std::string getLoggername() const { return loggername_; }

    //std::shared_ptr<Logger> getLogger() const { return logger_;}

    void format(const char *fmt, ...);

    void format(const char *fmt, va_list ap);

private:
    LogLevel::Level level_;
    std::stringstream ss_;
    const std::string filename_;
    uint64_t elapse_;
    uint64_t line_;
    uint64_t threadId_;
    uint64_t fiberId_;
    uint64_t time_;
    std::string threadname_;
    std::string loggername_;
    //std::shared_ptr<Logger> logger_;

};