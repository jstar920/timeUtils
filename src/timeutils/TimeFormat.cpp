#include "TimeFormat.h"
#include <LogHandler.h>

namespace timeutils
{
    const char* TimeFormat::ISO_8601_UTC_STR = "%Y-%m-%dT%H:%M:%SZ";               // example: 2023-09-20T15:42:09Z
    const char* TimeFormat::ISO_8601_UTC_MS_STR = "%Y-%m-%dT%H:%M:%S.#!@Z";        // example: 2023-09-20T15:42:09.998Z
    const char* TimeFormat::HTTP_HEAD_STR = "%a, %d %b %Y %H:%M:%S GMT";           // example: 20 Sep 2023 15:42:09 GMT
    const char* TimeFormat::LOG_TIMESTAMP_STR = "%Y-%m-%dT%H:%M:%S.#!@Z";          // example: 2023-09-20T15:42:09.998Z
    const char* TimeFormat::FILENAME_TIMESTAMP_STR = "%Y%m%d%H%M%S";               // example: 20230920154209
    const char* TimeFormat::DATABASE_TIMESTAMP_STR = "%s";                         // example: 1663771329
    const char* TimeFormat::CLOCK_STR = "%H:%M:%S";                                // example: 15:42:09
    const char* TimeFormat::DATE_STR = "%Y-%m-%d";                                 // example: 2023-09-20
    const char* TimeFormat::YEARMONTH_STR = "%Y-%m";                               // example: 2023-09
    const char* TimeFormat::HOURMINUTE_STR = "%H:%M";                              // example: 15:42

    const char* TimeFormat::PlaceHolder3_Str = "#!@";

    std::unordered_map<int, std::string> TimeFormat::sFmtPlaceHolders {
        {static_cast<int>(TimeFormatType::ISO_8601_UTC_MS), std::string(TimeFormat::PlaceHolder3_Str)}
    };

    const std::string TimeFormat::TimeFormatTypeSTARTStr(std::to_string(static_cast<int>(TimeFormatType::TimeFormatTypeSTART) + 1));
    const std::string TimeFormat::TimeFormatTypeENDStr(std::to_string(static_cast<int>(TimeFormatType::TimeFormatTypeEND) - 1));
    const std::string TimeFormat::TimeFormatRange("[" + TimeFormatTypeSTARTStr + ", " + TimeFormatTypeENDStr + "]");

    bool TimeFormat::isFormatTypeInRange(int fmtType)
    {
        return static_cast<int>(fmtType) > static_cast<int>(TimeFormatType::TimeFormatTypeSTART) && 
               static_cast<int>(fmtType) < static_cast<int>(TimeFormatType::TimeFormatTypeEND);
    }

    const char* TimeFormat::getFmtPlaceHolder(int fmtType)
    {
        const auto it = sFmtPlaceHolders.find(fmtType);
        if (it != sFmtPlaceHolders.cend())
        {
            return it->second.c_str();
        }

        return "";
    }

    void TimeFormat::registerFmtPlaceHolder(int fmtType, const std::string& placeHolder)
    {
        if (isFormatTypeInRange(fmtType))
        {
            LOG_ERROR("only can register id out of range:" + TimeFormatRange);
            return;
        }

        const auto it = sFmtPlaceHolders.find(fmtType);
        if (it != sFmtPlaceHolders.cend())
        {
            const auto current = "(" + std::to_string(fmtType) + ", " + placeHolder + ")";
            const auto previous = "(" + std::to_string(it->first) + ", " + it->second + ")";
            LOG_WARNING("register override " << previous << " by " << current);
        }
        sFmtPlaceHolders[fmtType] = placeHolder;
    }

    std::unordered_map<int, std::string> TimeFormat::sFmtStrs {
        { static_cast<int>(TimeFormatType::ISO_8601_UTC), TimeFormat::ISO_8601_UTC_STR},
        { static_cast<int>(TimeFormatType::ISO_8601_UTC_MS), TimeFormat::ISO_8601_UTC_MS_STR},
        { static_cast<int>(TimeFormatType::HTTP_HEAD), TimeFormat::HTTP_HEAD_STR},
        { static_cast<int>(TimeFormatType::LOG_TIMESTAMP), TimeFormat::LOG_TIMESTAMP_STR},
        { static_cast<int>(TimeFormatType::FILENAME_TIMESTAMP), TimeFormat::FILENAME_TIMESTAMP_STR},
        { static_cast<int>(TimeFormatType::DATABASE_TIMESTAMP), TimeFormat::DATABASE_TIMESTAMP_STR},
        { static_cast<int>(TimeFormatType::CLOCK), TimeFormat::CLOCK_STR},
        { static_cast<int>(TimeFormatType::DATE), TimeFormat::DATE_STR},
        { static_cast<int>(TimeFormatType::YEARMONTH), TimeFormat::YEARMONTH_STR},
        { static_cast<int>(TimeFormatType::HOURMINUTE), TimeFormat::HOURMINUTE_STR}
    };

    const char* TimeFormat::getFmtStr(int fmtType)
    {
        const auto it = sFmtStrs.find(fmtType);
        if (it != sFmtStrs.cend())
        {
            return it->second.c_str();
        }
        return "";
    }

    void TimeFormat::registerFmtStr(int fmtType, const std::string& str)
    {
        if (isFormatTypeInRange(fmtType))
        {
            LOG_ERROR("only can register id out of range:" + TimeFormatRange);
            return;
        }

        const auto it = sFmtStrs.find(fmtType);
        if (it != sFmtStrs.cend())
        {
            const auto current = "(" + std::to_string(fmtType) + ", " + str + ")";
            const auto previous = "(" + std::to_string(it->first) + ", " + it->second + ")";
            LOG_WARNING("register override " << previous << " by " << current);
        }
        sFmtStrs[fmtType] = str;
    }

    
    std::unordered_map<int, PlaceHolderHandler> TimeFormat::sFmtPlaceHolderHandlers {
        {static_cast<int>(TimeFormatType::ISO_8601_UTC_MS), TimeFormat::placeholderHandler_ISO_8601_UTC_MS},
        {static_cast<int>(TimeFormatType::LOG_TIMESTAMP),   TimeFormat::placeholderHandler_ISO_8601_UTC_MS}
    };

    PlaceHolderHandler TimeFormat::getFmtPlaceHolderHandler(int fmtType)
    {
        const auto it = sFmtPlaceHolderHandlers.find(fmtType);
        if (it != sFmtPlaceHolderHandlers.cend())
        {
            return it->second;
        }
        return nullptr;
    }

    void TimeFormat::registerFmtPlaceHolderHandler(int fmtType, const PlaceHolderHandler& handler)
    {
        if (isFormatTypeInRange(fmtType))
        {
            LOG_ERROR("only can register id out of range:" + TimeFormatRange);
            return;
        }

        const auto it = sFmtPlaceHolderHandlers.find(fmtType);
        if (it != sFmtPlaceHolderHandlers.cend())
        {
            LOG_WARNING("register override placeholder handler" << fmtType << " ");
        }
        sFmtPlaceHolderHandlers[fmtType] = handler;
    }

    /// <summary>
    /// pre-defined placeholder handlers
    /// </summary>
    void TimeFormat::placeholderHandler_ISO_8601_UTC_MS(char* buffer, const TimePoint& point)
    {
       const auto timeStampMs = std::chrono::duration_cast<std::chrono::milliseconds>(point.time_since_epoch()).count();
       char* pos = std::strstr(buffer, TimeFormat::PlaceHolder3_Str);
       if (pos != nullptr && (pos - buffer) > 3)
       {
            *pos = std::to_string(timeStampMs % 1000 / 100)[0];
            *(pos + 1) = std::to_string(timeStampMs % 100 / 10)[0];
            *(pos + 2) = std::to_string(timeStampMs % 10)[0];
       }
    }
}