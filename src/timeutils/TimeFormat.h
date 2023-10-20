#pragma once
#include <unordered_map>
#include <string>
#include <functional>


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

    static inline bool shouldShowMs(TimeFormatType type) {
        return (type == TimeFormatType::ISO_8601_UTC_MS ||
                type == TimeFormatType::LOG_TIMESTAMP);
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

        static const char* getFmtPlaceHolder(int fmtType);
        static void registerFmtPlaceHolder(int fmtType, const std::string& placeHolder);

        static const char* getFmtStr(int fmtType);
        static void registerFmtStr(int fmtType, const std::string& str);
    private:
        static std::unordered_map<int, std::string> sFmtPlaceHolders;
        static std::unordered_map<int, std::string> sFmtStr;
    };

    template<typename FmtType>
    inline const char* fmt(FmtType type){
        TimeFormat::getFmtStr(static_cast<int>(type));
    }

    template<typename FmtType>
    inline const char* fmtPlaceHolder(FmtType type){
        TimeFormat::getFmtPlaceHolder(static_cast<int>(type));
    }

}