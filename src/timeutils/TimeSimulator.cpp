#include "TimeSimulator.h"
#include "Timefunction.h"
#include "LogHandler.h"

namespace timeutils_simulator
{
    std::list<GetSteadyClockNow> TimeSimulator::sGetSteadyClockNowList;
    std::list<GetSystemClockNow> TimeSimulator::sGetSystemClockNowList;

    TimeSimulator::TimeSimulator(uint64_t steadyNowMs, uint64_t systemNowMs)
    : steady_clock_now_(std::chrono::milliseconds(steadyNowMs))
    , system_clock_now_(std::chrono::milliseconds(systemNowMs))
    , log_(std::make_shared<timeutils::LogHandler>())
    {
        steadyClockNowFunctionSize_ = sGetSteadyClockNowList.size();
        sGetSteadyClockNowList.push_back(timeutils::TimeFunction::getGetSteadyClockNow());
        timeutils::TimeFunction::setGetSteadyClockNow([this](){return steadyClockNow();});

        systemClockNowFunctionSize_ = sGetSystemClockNowList.size();
        sGetSystemClockNowList.push_back(timeutils::TimeFunction::getGetSystemClockNow());
        timeutils::TimeFunction::setGetSystemClockNow([this](){return systemClockNow();});
    }

     TimeSimulator::~TimeSimulator()
     {
         if (!sGetSteadyClockNowList.empty()) 
         {
             timeutils::TimeFunction::setGetSteadyClockNow(sGetSteadyClockNowList.back());
             sGetSteadyClockNowList.pop_back();
             if (sGetSteadyClockNowList.size() != steadyClockNowFunctionSize_)
             {
                 LOG_WARNING("steady clock is incorrect setting! you may set mutiple simulator");
             }
         }

         if (!sGetSystemClockNowList.empty()) 
         {
             timeutils::TimeFunction::setGetSystemClockNow(sGetSystemClockNowList.back());
             sGetSystemClockNowList.pop_back();
             if (sGetSystemClockNowList.size() != systemClockNowFunctionSize_)
             {
                 LOG_WARNING("system clock is incorrect setting! you may set mutiple simulator");
             }
         }
     }

    void TimeSimulator::steadyClockElapseMilliSeconds(uint64_t ms)
    {
        steady_clock_now_ += std::chrono::milliseconds(ms);
    }

    void TimeSimulator::steadyClockElapseSeconds(uint64_t s)
    {
        steady_clock_now_ += std::chrono::seconds(s);
    }

    void TimeSimulator::steadyClockElapseMinutes(uint64_t m)
    {
        steady_clock_now_ += std::chrono::minutes(m);
    }

    void TimeSimulator::steadyClockElapseHours(uint64_t h)
    {
        steady_clock_now_ += std::chrono::hours(h);
    }

    void TimeSimulator::steadyClockElapseDays(uint64_t d)
    {
        steady_clock_now_ += std::chrono::hours(d * 24);
    }

    void TimeSimulator::systemClockElapseMilliSeconds(uint64_t ms)
    {
        system_clock_now_ += std::chrono::milliseconds(ms);
    }

    void TimeSimulator::systemClockElapseSeconds(uint64_t s)
    {
        system_clock_now_ += std::chrono::seconds(s);
    }

    void TimeSimulator::systemClockElapseMinutes(uint64_t m)
    {
        system_clock_now_ += std::chrono::minutes(m);
    }

    void TimeSimulator::systemClockElapseHours(uint64_t h)
    {
        system_clock_now_ += std::chrono::hours(h);
    }

    void TimeSimulator::systemClockElapseDays(uint64_t d)
    {
        system_clock_now_ += std::chrono::hours(d * 24);
    }

    std::chrono::steady_clock::time_point TimeSimulator::steadyClockNow()
    {
        return steady_clock_now_;
    }

    std::chrono::system_clock::time_point TimeSimulator::systemClockNow()
    {
        return system_clock_now_;
    }
}