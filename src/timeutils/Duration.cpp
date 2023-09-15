#include "Duration.h"
namespace timeutils
{
    Duration::Duration()
    : startTime_(std::chrono::steady_clock::now())
    , lastCheckTime_(startTime_)
    {}

    std::chrono::steady_clock::duration Duration::checkDurationFromStart()
    {
        lastCheckTime_ = std::chrono::steady_clock::now();
        return lastCheckTime_ - startTime_;
    }

    std::chrono::steady_clock::duration  Duration::checkLastDurationFromLast()
    {
        const auto current = std::chrono::steady_clock::now();
        const auto duration = current - lastCheckTime_;
        lastCheckTime_ = current;
        return duration;
    }

    std::pair<std::chrono::steady_clock::duration, std::chrono::steady_clock::duration> Duration::checkLastDurationBoth()
    {
        const auto current = std::chrono::steady_clock::now();
        const auto durationFromStart = current - startTime_;
        const auto durationFromLast = current - lastCheckTime_;
        lastCheckTime_ = current;
        return {durationFromStart, durationFromLast};
    }
}