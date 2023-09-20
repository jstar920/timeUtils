#include <functional>
#include <chrono>

namespace timeutils
{
    using GetSteadyClockNow = std::function<std::chrono::steady_clock::time_point()>;
    class TimeFunction
    {
    public:
        static void setGetSteadyClockNow(const GetSteadyClockNow& func);
        static GetSteadyClockNow getGetSteadyClockNow();
    private:
        static GetSteadyClockNow sGetSteadyClockNow;
    };
}