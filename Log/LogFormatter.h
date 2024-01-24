#pragma once

#include <string>
#include <memory>
#include <vector>
#include <iostream>
#include <map>
#include <functional>
#include "LogLevel.h"
#include "LogEvent.h"
/**
 * %m 消息
 * %p 日志级别
 * %f 文件名
 * %r 累计毫秒
 * %l 行号
 * %t 线程id
 * %F 协程id
 * %d 时间
 * %N 线程名称
 * %c 日志名称
*/
class LogFormatter {
public:
    typedef std::shared_ptr<LogFormatter> ptr;

    LogFormatter(const std::string &pattern = "%d{%Y-%m-%d %H:%M:%S} [%rms]%T%t%T%N%T%F%T[%p]%T[%c]%T%f:%l%T%m%n");

    void init();

    std::string format(std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event);

    std::ostream &format(std::ostream& ofs, std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event);

    std::string getPattern() const { return pattern_; }

public:

    class FormatItem {
    public:
        typedef std::shared_ptr<FormatItem> ptr;
        
        virtual ~FormatItem() {}

        virtual void format(std::ostream &os, std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event) = 0;
    };

private:

    std::string pattern_;

    std::vector<FormatItem::ptr> items_;

};


/**

 * MessageFormatItem
 * LevelFormatItem
 * FilenameFormatItem
 * ElapseFormatItem
 * LineFormatItem
 * ThreadIdFormatItem
 * FiberIdFormatItem
 * DateTimeFormatItem
 * ThreadNameFormatItem
 * LoggerNameFormatItem
*/