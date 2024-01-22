#include "LogEventWrap.h"

LogEventWrap::LogEventWrap(LogEvent::ptr e)
    :event_(e) 
{
}

LogEventWrap::~LogEventWrap() 
{
    logger_->log(event_->getLevel(), event_);
}