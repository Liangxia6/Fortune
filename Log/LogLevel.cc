#include "LogLevel.h"

static const std::string LogLevel::(LogLevel::Level level)
{
    switch(level) 
    {
        case LogLevel::Level::DEBG :
            return "DEBG";
            break;
        case LogLevel::Level::INFO :
            return "INFO";
            break;
        case LogLevel::Level::WRAN :
            return "WARN";
            break;
        case LogLevel::Level::FATL :
            return "FATL";
            break;
        default :
            return "UKNO";
    }
}

LogLevel::Level LogLevel::FromString(const std::string& str)
{
    if(str == "DEBG")
    {
        return LogLevel::DEBG;
    }
    else if(str == "INFO")
    {
        return LogLevel::INFO;
    }
    else if(str == "WARN")
    {
        return LogLevel::WRAN;
    }
    else if(str == "FATL")
    {
        return LogLevel::FATL;
    }
}
