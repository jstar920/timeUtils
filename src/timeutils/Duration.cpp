#include "Duration.h"
#include "TimeFunction.h"

namespace timeutils
{
    Duration::Duration(const std::function<void(const uint64_t& msSecond)>& handle)
    : startTime_(TimeFunction::getGetSteadyClockNow() ? TimeFunction::getGetSteadyClockNow()() : std::chrono::steady_clock::now())
    , lastCheckTime_(startTime_)
    , totalDurationHandle_(handle)
    {}

    Duration::~Duration()
    {
        const auto duration = updateDurationFromStart();
        if (totalDurationHandle_)
        {
            totalDurationHandle_(std::chrono::duration_cast<std::chrono::milliseconds>(duration).count());
        }
    }

    uint64_t Duration::getLastDurationMs()
    {
        return std::chrono::duration_cast<std::chrono::milliseconds>(updateLastDurationFromLast()).count();
    }

    uint64_t Duration::getTotalDurationMs()
    {
        return std::chrono::duration_cast<std::chrono::milliseconds>(updateDurationFromStart()).count();
    }

    std::chrono::steady_clock::duration Duration::updateDurationFromStart()
    {
        auto getSteadyClockNow = TimeFunction::getGetSteadyClockNow();
        lastCheckTime_ = getSteadyClockNow ? getSteadyClockNow() : std::chrono::steady_clock::now();
        return lastCheckTime_ - startTime_;
    }

    std::chrono::steady_clock::duration  Duration::updateLastDurationFromLast()
    {
        auto getSteadyClockNow = TimeFunction::getGetSteadyClockNow();
        const auto current = getSteadyClockNow ? getSteadyClockNow() : std::chrono::steady_clock::now();
        const auto duration = current - lastCheckTime_;
        lastCheckTime_ = current;
        return duration;
    }

    std::pair<std::chrono::steady_clock::duration, std::chrono::steady_clock::duration> Duration::checkLastDurationBoth()
    {
        auto getSteadyClockNow = TimeFunction::getGetSteadyClockNow();
        const auto current = getSteadyClockNow ? getSteadyClockNow() : std::chrono::steady_clock::now();
        const auto durationFromStart = current - startTime_;
        const auto durationFromLast = current - lastCheckTime_;
        lastCheckTime_ = current;
        return {durationFromStart, durationFromLast};
    }
}