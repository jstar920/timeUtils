#pragma once
#include <functional>
#include <chrono>
#include <list>
#include <mutex>

using GetSteadyClockNow = std::function<std::chrono::steady_clock::time_point()>;
using GetSystemClockNow = std::function<std::chrono::system_clock::time_point()>;

namespace timeutils
{
    struct LogHandler;
}

namespace timeutils_simulator
{
    class TimeSimulator
    {
    public:
        TimeSimulator(uint64_t steadyNowMs = 10000000, uint64_t systemNowMs = 10000000);
        ~TimeSimulator();

        void steadyClockElapseMilliSeconds(uint64_t ms);
        void steadyClockElapseSeconds(uint64_t s);
        void steadyClockElapseMinutes(uint64_t m);
        void steadyClockElapseHours(uint64_t h);
        void steadyClockElapseDays(uint64_t d);

        void systemClockElapseMilliSeconds(uint64_t ms);
        void systemClockElapseSeconds(uint64_t s);
        void systemClockElapseMinutes(uint64_t m);
        void systemClockElapseHours(uint64_t h);
        void systemClockElapseDays(uint64_t d);

    private:
        std::chrono::steady_clock::time_point steadyClockNow();
        std::chrono::system_clock::time_point systemClockNow();
    private:
        std::chrono::steady_clock::time_point steady_clock_now_ {std::chrono::seconds(10000)};
        std::chrono::system_clock::time_point system_clock_now_ {std::chrono::seconds(10000)};

        size_t steadyClockNowFunctionSize_ {0};
        size_t systemClockNowFunctionSize_ {0};

        static std::list<GetSteadyClockNow> sGetSteadyClockNowList;
        static std::list<GetSystemClockNow> sGetSystemClockNowList;

        std::shared_ptr<timeutils::LogHandler> log_;
    };
}