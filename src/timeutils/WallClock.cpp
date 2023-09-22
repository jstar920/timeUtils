#include "WallClock.h"
#include "timeFunction.h"

namespace timeutils
{
    uint64_t WallClock::getCurrentTimeUTCAsMs()
    {
        auto getSystemClockNow = TimeFunction::getGetSystemClockNow();
        const auto current = getSystemClockNow ? getSystemClockNow() : std::chrono::system_clock::now(); 
        std::chrono::duration_cast<std::chrono::milliseconds>(current.time_since_epoch()).count();
    }

    std::string WallClock::getCurrentTimeUTCAsString()
    {
        auto getSystemClockNow = TimeFunction::getGetSystemClockNow();
        const auto current = getSystemClockNow ? getSystemClockNow() : std::chrono::system_clock::now();
        std::time_t current_time = std::chrono::system_clock::to_time_t(current);
        std::tm* tm = std::gmtime(&current_time);
        char buffer[80];
        const auto localTimeStr = std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", tm);

        const auto milli = std::chrono::duration_cast<std::chrono::milliseconds>(current.time_since_epoch()).count() % 1000;
        return localTimeStr + "." + std::to_string(milli);
    }
}