#include "TimeFunction.h"
namespace timeutils
{
    GetSteadyClockNow TimeFunction::sGetSteadyClockNow = std::chrono::steady_clock::now;
    GetSystemClockNow TimeFunction::sGetSystemClockNow = std::chrono::system_clock::now;
    void TimeFunction::setGetSteadyClockNow(const GetSteadyClockNow& func)
    {
        sGetSteadyClockNow = func;
    }

    GetSteadyClockNow TimeFunction::getGetSteadyClockNow()
    {
        return sGetSteadyClockNow;
    }

    void TimeFunction::setGetSystemClockNow(const GetSystemClockNow& func)
    {
        sGetSystemClockNow = func;
    }

    GetSystemClockNow TimeFunction::getGetSystemClockNow()
    {
        return sGetSystemClockNow;
    }
}