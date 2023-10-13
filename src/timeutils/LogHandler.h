#include <string>
#include <functional>
namespace timeutils
{
    struct LogHandler
    {
        enum LogLevel {
            Debug,
            Info,
            Warning,
            Error
        };

        void log(LogLevel level, const std::string& msg);

        static void setLogHandler(const std::function<void(const std::string& msg)>& logHandler);
    private:
        static std::function<void(const std::string& msg)> sLog;
    };
};