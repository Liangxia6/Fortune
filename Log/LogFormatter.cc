#include "LogFormatter.h"

LogFormatter::LogFormatter(const std::string& pattern)
    :pattern_(pattern)
{
    init();
}

void LogFormatter::init()
{
    
}

std::string LogFormatter::format(std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event)
{
    std::stringstream ss;
    for (auto& i : items_)
    {
        i->format(ss, logger, level, event);
    }
    return ss.str();
}

std::ostream& LogFormatter::format(std::ostream& ofs, std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event)
{
    for (auto& i : items_)
    {
        i->format(ofs, logger, level, event);
    }
    return ofs;
}


class MessageFormatItem : public LogFormatter::FormatItem 
{
public:
    MessageFormatItem(const std::string& str = "") {}

    void format(std::ostream& os, Logger::ptr logger, LogLevel::Level level, LogEvent::ptr event) override 
    {
        os << event->getContent();
    }
};

class LevelFormatItem : public LogFormatter::FormatItem 
{
public:
    LevelFormatItem(const std::string& str = "") {}

    void format(std::ostream& os, Logger::ptr logger, LogLevel::Level level, LogEvent::ptr event) override 
    {
        os << LogLevel::ToString(level);
    }
};

class FilenameFormatItem : public LogFormatter::FormatItem 
{
public:
    FilenameFormatItem(const std::string& str = "") {}

    void format(std::ostream& os, Logger::ptr logger, LogLevel::Level level, LogEvent::ptr event) override 
    {
        os << event->getFilename();
    }
};

class ElapseFormatItem : public LogFormatter::FormatItem 
{
public:
    ElapseFormatItem(const std::string& str = "") {}

    void format(std::ostream& os, Logger::ptr logger, LogLevel::Level level, LogEvent::ptr event) override 
    {
        os << event->getElapse();
    }
};

class LineFormatItem : public LogFormatter::FormatItem 
{
public:
    LineFormatItem(const std::string& str = "") {}

    void format(std::ostream& os, Logger::ptr logger, LogLevel::Level level, LogEvent::ptr event) override 
    {
        os << event->getLine();
    }
};

class ThreadIdFormatItem : public LogFormatter::FormatItem 
{
public:
    ThreadIdFormatItem(const std::string& str = "") {}

    void format(std::ostream& os, Logger::ptr logger, LogLevel::Level level, LogEvent::ptr event) override 
    {
        os << event->getThreadId();
    }
};

class FiberIdFormatItem : public LogFormatter::FormatItem 
{
public:
    FiberIdFormatItem(const std::string& str = "") {}

    void format(std::ostream& os, Logger::ptr logger, LogLevel::Level level, LogEvent::ptr event) override 
    {
        os << event->getFiberId();
    }
};

class DateTimeFormatItem : public LogFormatter::FormatItem 
{
public:
    DateTimeFormatItem(const std::string& format = "%Y-%m-%d %H:%M:%S")
        :format_(format) 
    {
        if(format_.empty()) 
        {
            format_ = "%Y-%m-%d %H:%M:%S";
        }
    }

    void format(std::ostream& os, Logger::ptr logger, LogLevel::Level level, LogEvent::ptr event) override 
    {
        struct tm tm;
        time_t time = event->getTime();
        localtime_r(&time, &tm);
        char buf[64];
        strftime(buf, sizeof(buf), format_.c_str(), &tm);
        os << buf;
    }
private:
    std::string format_;
};

class ThreadNameFormatItem : public LogFormatter::FormatItem 
{
public:
    ThreadNameFormatItem(const std::string& str = "") {}

    void format(std::ostream& os, Logger::ptr logger, LogLevel::Level level, LogEvent::ptr event) override 
    {
        os << event->getThreadname();
    }
};

class NameFormatItem : public LogFormatter::FormatItem 
{
public:
    NameFormatItem(const std::string& str = "") {}

    void format(std::ostream& os, Logger::ptr logger, LogLevel::Level level, LogEvent::ptr event) override 
    {
        os << event->getLoggername();
    }
};