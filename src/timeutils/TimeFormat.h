#pragma once
#include <unordered_map>
#include <string>
#include <functional>
#include <chrono>


namespace timeutils
{
    enum class TimeFormatType {
        TimeFormatTypeSTART,
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
        TimeFormatTypeEND
    };

    static inline bool shouldShowMs(TimeFormatType type) {
        return (type == TimeFormatType::ISO_8601_UTC_MS ||
                type == TimeFormatType::LOG_TIMESTAMP);
    }

    using TimePoint = std::chrono::system_clock::time_point;
    using PlaceHolderHandler = std::function<void(char*, const TimePoint&)>;
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

        static PlaceHolderHandler getFmtPlaceHolderHandler(int fmtType);
        static void registerFmtPlaceHolderHandler(int fmtType, const PlaceHolderHandler& handler);

    private:
        static bool isFormatTypeInRange(int fmtType);

        static std::unordered_map<int, std::string> sFmtPlaceHolders;
        static std::unordered_map<int, std::string> sFmtStrs;
        static std::unordered_map<int, PlaceHolderHandler> sFmtPlaceHolderHandlers;

        static const std::string TimeFormatTypeSTARTStr;
        static const std::string TimeFormatTypeENDStr;
        static const std::string TimeFormatRange;

        static void placeholderHandler_ISO_8601_UTC_MS(char* buffer, const TimePoint& point);
    };

    template<typename FmtType>
    inline void registerFmtPlaceHolder(FmtType fmtType, const std::string& placeHolder)
    {
        static_assert(!std::is_same<FmtType, TimeFormatType>::value, "TimeFormatType type is inner type, can not override register");
        TimeFormat::registerFmtPlaceHolder(static_cast<int>(fmtType), placeHolder);
    }

    template<typename FmtType>
    inline const char* fmtPlaceHolder(FmtType type){
        return TimeFormat::getFmtPlaceHolder(static_cast<int>(type));
    }

    template<typename FmtType>
    inline void registerFmtStr(FmtType fmtType, const std::string& str)
    {
        static_assert(!std::is_same<FmtType, TimeFormatType>::value, "TimeFormatType type is inner type, can not override register");
        TimeFormat::registerFmtStr(static_cast<int>(fmtType), str);
    }

    template<typename FmtType>
    inline const char* fmt(FmtType type){
        return TimeFormat::getFmtStr(static_cast<int>(type));
    }

    template<typename FmtType>
    inline void registerFmtPlaceHolderHandler(FmtType fmtType, const PlaceHolderHandler& handler)
    {
        static_assert(!std::is_same<FmtType, TimeFormatType>::value, "TimeFormatType type is inner type, can not override register");
        TimeFormat::registerFmtPlaceHolderHandler(static_cast<int>(fmtType), handler);
    }

    template<typename FmtType>
    inline PlaceHolderHandler fmtPlaceHolderHandler(FmtType type){
        return TimeFormat::getFmtPlaceHolderHandler(static_cast<int>(type));
    }
}