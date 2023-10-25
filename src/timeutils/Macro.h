#pragma once
#include <sstream>

#ifndef LOG_DEBUG
    #define LOG_DEBUG(msg) timeutils::LogDebug((std::stringstream() << __FILE__ << " " << __LINE__ << " " << __FUNCTION__ << " " << msg).str())
#endif

#ifndef LOG_INFO
    #define LOG_INFO(msg) timeutils::LogInfo((std::stringstream() << __FILE__ << " " << __LINE__ << " " << __FUNCTION__ << " " << msg).str())
#endif

#ifndef LOG_WARNING
    #define LOG_WARNING(msg) timeutils::LogWarning((std::stringstream() << __FILE__ << " " << __LINE__ << " " << __FUNCTION__ << " " << msg).str())
#endif

#ifndef LOG_ERROR
    #define LOG_ERROR(msg) timeutils::LogError((std::stringstream() << __FILE__ << " " << __LINE__ << " " << __FUNCTION__ << " " << msg).str())
#endif
