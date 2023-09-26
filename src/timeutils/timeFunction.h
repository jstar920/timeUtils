#include <functional>
#include <chrono>

namespace timeutils
{
    using GetSteadyClockNow = std::function<std::chrono::steady_clock::time_point()>;
    using GetSystemClockNow = std::function<std::chrono::system_clock::time_point()>;
    class TimeFunction
    {
    public:
        static void setGetSteadyClockNow(const GetSteadyClockNow& func);
        static GetSteadyClockNow getGetSteadyClockNow();

        static void setGetSystemClockNow(const GetSystemClockNow& func);
        static GetSystemClockNow getGetSystemClockNow();
    private:
        static GetSteadyClockNow sGetSteadyClockNow;
        static GetSystemClockNow sGetSystemClockNow;
    };
}