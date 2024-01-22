#pragma once

#include <string>
#include <memory>
#include <list>
#include "LogFormatter.h"
#include "LogAppender.h"

class Logger : public std::enable_shared_from_this<Logger> {
public:
    friend class LoggerManager;

    typedef std::shared_ptr<Logger> ptr;
    typedef Spinlock MutexType;

    Logger(const std::string& name = "root");

    void log(LogLevel::Level level, LogEvent::ptr event);
    void debg(LogEvent::ptr event);
    void info(LogEvent::ptr event);
    void warn(LogEvent::ptr event);
    void fatl(LogEvent::ptr event);

    void addAppender(LogAppender::ptr appender);

    void delAppender(LogAppender::ptr appender);

    void clearAppenders();

    LogLevel::Level getLevel() const { return level_; }

    void setLevel(LogLevel::Level val) { level_ = val; }

    const std::string& getName() const { return name_; }

    LogFormatter::ptr getFormatter();

    std::string toYamlString();

private:
    std::string name_;
    LogLevel::Level level_;
    MutexType mutex_;
    std::list<LogAppender::ptr> appenders_;

};