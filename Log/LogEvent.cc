#include "LogEvent.h"

LogEvent::LogEvent(const std::string& loggerName, LogLevel::Level level, 
            const std::string fileName, uint64_t line, 
            uint64_t elapse, uint64_t threadId, uint64_t fiberId, 
            uint64_t time, const std::string& threadName)
            : loggername_(loggerName)
            , level_(level)
            , filename_(fileName)
            , line_(line)
            , elapse_(elapse)
            , threadId_(threadId)
            , fiberId_(fiberId)
            , time_(time)
            , threadname_(threadName)
{

}

void LogEvent::format(const char *fmt, ...)
{
    va_list al;
    va_start(al, fmt);
    format(fmt, al);
    va_end(al);
}

void LogEvent::format(const char* fmt, va_list al) 
{
    char* buf = nullptr;
    int len = vasprintf(&buf, fmt, al);
    if(len != -1) 
    {
        ss_ << std::string(buf, len);
        free(buf);
    }
}