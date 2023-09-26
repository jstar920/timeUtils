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

    std::string WallClock::getCurrentTimeUTCAsString(TimeFormatType type)
    {
        auto getSystemClockNow = TimeFunction::getGetSystemClockNow();
        const auto current = getSystemClockNow ? getSystemClockNow() : std::chrono::system_clock::now();
        const auto timeStampS = std::chrono::duration_cast<std::chrono::seconds>(current.time_since_epoch()).count();
        std::tm* tm = std::gmtime(&timeStampS);
        char buffer[80];
        const auto localTimeStr = std::strftime(buffer, sizeof(buffer), fmt(type), tm);
        return std::string(buffer);

        if (shouldShowMs(type))
        {
            const auto timeStampMs = std::chrono::duration_cast<std::chrono::milliseconds>(current.time_since_epoch()).count();
            char* pos = std::strstr(buffer, TimeFormat::PlaceHolder3_Str);
            if (pos != nullptr && (pos - buffer) > 3)
            {
                *pos = std::to_string(timeStampMs % 1000 / 100)[0];
                *(pos + 1) = std::to_string(timeStampMs % 100 / 10)[0];
                *(pos + 2) = std::to_string(timeStampMs % 10)[0];
                *(pos + 3) = 0;
            }
        }

        return std::string(buffer);
    }
}