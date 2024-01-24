#include "LogFormatter.h"

LogFormatter::LogFormatter(const std::string& pattern)
    :pattern_(pattern)
{
    init();
}

void LogFormatter::init()
{
    std::vector<std::tuple<std::string, std::string, int>> vec;
    std::string nstr;
    //%xxx %xxx{xxx} %%
    for (size_t i = 0; i < pattern_.size(); i++)
    {
        if (pattern_[i] != '%')
        {
            nstr.append(1, pattern_[i]);
            continue;
        }
        if ((i + 1) < pattern_.size())
        {
            if (pattern_[i + 1] == '%')
            {
                nstr.append(1, '%');
                continue;
            }
        }
        size_t n = i + 1;
        int fmt_status = 0;
        size_t fmt_begin = 0;
        std::string str;
        std::string fmt;
        while (n < pattern_.size())
        {
            if (!fmt_status && (!isalpha(pattern_[n] && pattern_[n] != '{}' && pattern_[n] != '}')))
            {
                str = pattern_.substr(1+1, n-i-1);
                break;
            }
            if (fmt_status == 0)
            {
                if (pattern_[n] == '{')
                {
                    str = pattern_.substr(i+1, n-i-1);
                    fmt_status = 1;
                    fmt_begin = n;
                    n++;
                    continue;
                }
            }
            else if (fmt_status == 1)
            {
                if (pattern_[n] == '}')
                {
                    fmt = pattern_.substr(fmt_begin+1, n-fmt_begin-1);
                    fmt_status = 0;
                    n++;
                    break;
                }
            }
            n++;
            if (n == pattern_.size())
            {
                if (str.empty())
                {
                    str = pattern_.substr(i+1);
                }
            }
        }
        
        if (fmt_status == 0)
        {
            if (!nstr.empty())
            {
                vec.push_back(std::make_tuple(nstr, std::string(), 0));
                nstr.clear();
            }
            vec.push_back(std::make_tuple(str, fmt, 1));
            i = n - 1;
        }
        else if (fmt_status == 1)
        {
            std::cout << "pattern error: " << pattern_ << std::endl;
            vec.push_back(std::make_tuple("<<error>>", fmt, 0));
        }
    }
    
    if (!nstr.empty())
    {
        vec.push_back(std::make_tuple(nstr, "", 0));
    }
    static std::map<std::string, std::function<FormatItem::ptr(const std::string& str)>> format_items = 
    {
        {"m", [](const std::string& fmt) { return FormatItem::ptr(new MessageFormatItem(fmt)); }},
        {"p", [](const std::string& fmt) { return FormatItem::ptr(new LevelFormatItem(fmt)); }},
        {"f", [](const std::string& fmt) { return FormatItem::ptr(new FilenameFormatItem(fmt)); }},
        {"r", [](const std::string& fmt) { return FormatItem::ptr(new ElapseFormatItem(fmt)); }},
        {"l", [](const std::string& fmt) { return FormatItem::ptr(new LineFormatItem(fmt)); }},
        {"t", [](const std::string& fmt) { return FormatItem::ptr(new ThreadIdFormatItem(fmt)); }},
        {"F", [](const std::string& fmt) { return FormatItem::ptr(new FiberIdFormatItem(fmt)); }},
        {"d", [](const std::string& fmt) { return FormatItem::ptr(new DateTimeFormatItem(fmt)); }},
        {"N", [](const std::string& fmt) { return FormatItem::ptr(new ThreadNameFormatItem(fmt)); }},
        {"c", [](const std::string& fmt) { return FormatItem::ptr(new LoggerNameFormatItem(fmt)); }},
    };
    
    for (auto& i : vec)
    {
        if (std::get<2>(i) == 0)
        {
            items_.push_back(FormatItem::ptr(new StringFormatItem(std::get<0>(i))));
        }
        else
        {
            auto it = format_items.find(std::get<0>(i));
            if (it == format_items.end())
            {
                items_.push_back(FormatItem::ptr(new StringFormatItem("<<error_format %" + std::get<0>(i) + ">>")));
            }
            else
            {
                items_.push_back(it->second(std::get<1>(i)));
            }
        }
    }
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

class LoggerNameFormatItem : public LogFormatter::FormatItem 
{
public:
    LoggerNameFormatItem(const std::string& str = "") {}

    void format(std::ostream& os, Logger::ptr logger, LogLevel::Level level, LogEvent::ptr event) override 
    {
        os << event->getLoggername();
    }
};

class StringFormatItem : public LogFormatter::FormatItem 
{
public:
    StringFormatItem(const std::string& str)
        :m_string(str) {}
    
    void format(std::ostream& os, Logger::ptr logger, LogLevel::Level level, LogEvent::ptr event) override 
    {
        os << m_string;
    }
private:
    std::string m_string;
};
