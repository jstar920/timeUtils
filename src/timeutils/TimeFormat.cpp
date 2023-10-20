#pragma once
#include "TimeFormat.h"
#include <string_view>

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
        {ISO_8601_UTC_MS, PlaceHolder3_Str}
    };
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
        sFmtPlaceHolders[fmtType] = placeHolder;
    }

    std::unordered_map<int, std::string> TimeFormat::sFmtStr {
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
        const auto it = sFmtStr.find(fmtType);
        if (it != sFmtStr.cend())
        {
            return it->second.c_str();
        }
        return "";
    }

    void TimeFormat::registerFmtStr(int fmtType, const std::string& str)
    {
        sFmtStr[fmtType] = str;
    }

    {
        switch (TimeFormatType(type))
        {
        case TimeFormatType::ISO_8601_UTC: return TimeFormat::ISO_8601_UTC_STR;
        case TimeFormatType::ISO_8601_UTC_MS: return TimeFormat::ISO_8601_UTC_MS_STR;
        case TimeFormatType::HTTP_HEAD: return TimeFormat::HTTP_HEAD_STR;
        case TimeFormatType::LOG_TIMESTAMP: return TimeFormat::LOG_TIMESTAMP_STR;
        case TimeFormatType::FILENAME_TIMESTAMP: return TimeFormat::FILENAME_TIMESTAMP_STR;
        case TimeFormatType::DATABASE_TIMESTAMP: return TimeFormat::DATABASE_TIMESTAMP_STR;
        case TimeFormatType::CLOCK: return TimeFormat::CLOCK_STR;
        case TimeFormatType::DATE: return TimeFormat::DATE_STR;
        case TimeFormatType::YEARMONTH: return TimeFormat::YEARMONTH_STR;
        case TimeFormatType::HOURMINUTE: return TimeFormat::HOURMINUTE_STR;
        }

        return TimeFormat::getFmtStr(type);
    }
}