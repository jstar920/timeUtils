#include <stdint.h>
#include <string>
namespace timeutils
{
    enum class TimeFormatType;
    struct WallClock
    {
        static uint64_t getCurrentTimeUTCAsMs();
        static std::string getCurrentTimeUTCAsLogTimestamp();
        static std::string getCurrentTimeUTCAsString(TimeFormatType type);
        static std::string getCurrentTimeUTCAsString(const std::string& strFormat);
    };
}