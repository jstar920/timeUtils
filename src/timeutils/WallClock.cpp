#include "WallClock.h"
#include "TimeFunction.h"
#include "TimeFormat.h"
#include <cstring>

namespace timeutils
{
    uint64_t WallClock::getCurrentTimeUTCAsMs()
    {
        auto getSystemClockNow = TimeFunction::getGetSystemClockNow();
        const auto current = getSystemClockNow ? getSystemClockNow() : std::chrono::system_clock::now(); 
        return std::chrono::duration_cast<std::chrono::milliseconds>(current.time_since_epoch()).count();
    }

    std::string WallClock::getCurrentTimeUTCAsLogTimestamp()
    {
        return getCurrentTimeUTCAsString(TimeFormatType::LOG_TIMESTAMP);
    }

    std::string WallClock::getCurrentTimeUTCAsString(int type)
    {
        auto getSystemClockNow = TimeFunction::getGetSystemClockNow();
        const auto current = getSystemClockNow ? getSystemClockNow() : std::chrono::system_clock::now();
        const auto timeStampS = std::chrono::duration_cast<std::chrono::seconds>(current.time_since_epoch()).count();
        std::tm tm;
        gmtime_s(&tm, &timeStampS);
        char buffer[80];
        const auto localTimeStr = std::strftime(buffer, sizeof(buffer), fmt(type), &tm);

        const auto handler = fmtPlaceHolderHandler(type);
        if (handler)
        {
            handler(buffer, current);
        }

        return std::string(buffer);
    }
}