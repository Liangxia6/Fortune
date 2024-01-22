#pragma once

#include <string>

class LogLevel {
public:
    enum Level{
        DEBG = 0,
        INFO = 1,
        WRAN = 2,
        FATL = 3
    };

    static const std::string ToString(LogLevel::Level level);

    static LogLevel::Level FromString(const std::string& str);
    
};