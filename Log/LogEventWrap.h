#pragma once

#include "LogEvent.h"
#include "Logger.h"

class LogEventWrap {
public:

    LogEventWrap(LogEvent::ptr e);
    ~LogEventWrap();

    LogEvent::ptr getEvent() const { return event_;}

private:

    LogEvent::ptr event_;

    Logger::ptr logger_;
};