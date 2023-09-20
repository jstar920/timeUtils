#include "timeFunction.h"
namespace timeutils
{
    GetSteadyClockNow TimeFunction::sGetSteadyClockNow = std::chrono::steady_clock::now;
    void TimeFunction::setGetSteadyClockNow(const GetSteadyClockNow& func)
    {
        sGetSteadyClockNow = func;
    }

    GetSteadyClockNow TimeFunction::getGetSteadyClockNow()
    {
        return sGetSteadyClockNow;
    }
}