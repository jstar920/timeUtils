#pragma once
#include <string_view>


namespace timeutils
{
    enum class TimeFormatType {
        ISO_8601_UTC,
        ISO_8601_UTC_MS,
        HTTP_HEAD,
        LOG_TIMESTAMP,
        FILENAME_TIMESTAMP,
        DATABASE_TIMESTAMP,
        CLOCK,
        DATE,
        YEARMONTH,
        HOURMINUTE,
    };

    bool shouldShowMs(TimeFormatType type) {
        return (type == TimeFormatType::ISO_8601_UTC_MS);
    }

    struct TimeFormat
    {
        static const char* ISO_8601_UTC_STR;
        static const char* ISO_8601_UTC_MS_STR;
        static const char* HTTP_HEAD_STR;
        static const char* LOG_TIMESTAMP_STR;
        static const char* FILENAME_TIMESTAMP_STR;
        static const char* DATABASE_TIMESTAMP_STR;
        static const char* CLOCK_STR;
        static const char* DATE_STR;
        static const char* YEARMONTH_STR;
        static const char* HOURMINUTE_STR;

        static const char* PlaceHolder3_Str;
    };

    const char* fmt(TimeFormatType type);
}