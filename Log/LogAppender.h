#pragma once

#include <string>
#include <memory>
#include "Spinlock.h"
#include "LogFormatter.h"


class LogAppender {
public:
    typedef std::shared_ptr<LogAppender> ptr;
    typedef Spinlock MutexType;

    LogAppender(LogFormatter::ptr default_formatter);

    virtual ~LogAppender() {}

    void setFormatter(LogFormatter::ptr val);

    LogFormatter::ptr getFormatter();

    virtual void log(LogEvent::ptr event) = 0;
    virtual std::string toYamlString() = 0;

protected:
    MutexType mutex_;

    LogFormatter::ptr formatter_;
};



class StdoutLogAppender : public LogAppender {
public:
    typedef std::shared_ptr<StdoutLogAppender> ptr;

    StdoutLogAppender();

    void log(LogEvent::ptr event) override;

    std::string toYamlString() override;
};

class FileLogAppender : public LogAppender {
public:
    typedef std::shared_ptr<FileLogAppender> ptr;

    FileLogAppender();

    void log(LogEvent::ptr event) override;

    std::string toYamlString() override;
};