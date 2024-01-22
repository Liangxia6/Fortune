#pragma

#include <string>
#include <map>
#include "Spinlock.h"
#include "Logger.h"

class LoggerManager {
public:
    typedef Spinlock MutexType;

    LoggerManager();

    void init();

    Logger::ptr gtLogger(const std::string& name);

    Logger::ptr getRoot() { return root_; }

    std::string toYamlStirng();

private:
    MutexType mutex_;

    std::map<std::string, Logger::ptr> loggers_;

    Logger::ptr root_;
};
