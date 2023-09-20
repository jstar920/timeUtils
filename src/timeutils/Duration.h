#pragma once
#include <iostream>
#include <chrono>
#include <functional>

namespace timeutils
{
    class Duration
    {
    public:
        Duration(const std::function<void(const uint64_t& msSecond)>& handle = std::function<void(const uint64_t& msSecond)>());
        ~Duration();
        uint64_t getLastDurationMs();
        uint64_t getTotalDurationMs();
    private:
        std::chrono::steady_clock::duration updateDurationFromStart();
        std::chrono::steady_clock::duration updateLastDurationFromLast();
        std::pair<std::chrono::steady_clock::duration, std::chrono::steady_clock::duration> checkLastDurationBoth();
    private:
        std::chrono::steady_clock::time_point startTime_;
        std::chrono::steady_clock::time_point lastCheckTime_;
        std::function<void(const uint64_t& msSecond)> totalDurationHandle_;
    };
}