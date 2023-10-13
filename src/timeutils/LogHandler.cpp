#include "LogHandler.h"
#include <iostream>

namespace timeutils
{
    std::function<void(const std::string& msg)> LogHandler::sLog;
    void LogHandler::log(LogLevel level, const std::string& msg)
    {
        std::cout << msg << std::endl;
    }

    void LogHandler::setLogHandler(const std::function<void(const std::string& msg)>& logHandler)
    {
        sLog = logHandler;
    }
}
