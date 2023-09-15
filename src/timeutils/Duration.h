#pragma once
#include <iostream>
#include <chrono>

namespace timeutils
{
    class Duration
    {
    public:
    private:
        std::chrono::steady_clock::duration checkDurationFromStart();
        std::chrono::steady_clock::duration checkLastDurationFromLast();
        std::pair<std::chrono::steady_clock::duration, std::chrono::steady_clock::duration> checkLastDurationBoth();
    private:
        std::chrono::steady_clock::time_point startTime_;
        std::chrono::steady_clock::time_point lastCheckTime_;
    };
}