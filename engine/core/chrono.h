#pragma once
#include "types.h"
#include <chrono>

namespace deadrop
{
    // a high-resolution time class that can be used to build
    // more time-sensitive classes such as timers
    class Chrono
    {
    public:
        using time_point = std::chrono::steady_clock::time_point;

        // returns a high-resolution timepoint that can be used to calculate time difference between two different timepoints
        [[nodiscard]]
        inline static time_point GetHighResolutionNowTimepoint();

        // returns the time difference between two different time points in micro-seconds
        [[nodiscard]]
        inline static f64 GetTimepointDifference(time_point start, time_point end);

        // returns the number of milliseconds since the clock's epoch
        // NOTE: this clock is steady which means it will only increment, will not go back in time
        [[nodiscard]] static u64 GetHighResolutionTimeSinceEpoch();

        // returns the number of milliseconds since the first call to this function
        // NOTE: call this function at the very start of the program to get the time since the start
        // NOTE: this function uses a static variable to initialize the first time point
        [[nodiscard]] static u64 GetHighResolutionSinceFirstCall();
    };

    Chrono::time_point Chrono::GetHighResolutionNowTimepoint()
    {
        return std::chrono::steady_clock::now();
    }

    f64 Chrono::GetTimepointDifference(Chrono::time_point start, Chrono::time_point end)
    {
        auto time_difference_microseconds = std::chrono::duration_cast<std::chrono::microseconds>
            (end - start).count();
        return static_cast<f64>(time_difference_microseconds);
    }

    u64 Chrono::GetHighResolutionTimeSinceEpoch()
    {
        auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>
            (std::chrono::steady_clock::now().time_since_epoch()).count();
        return milliseconds;
    }

    u64 Chrono::GetHighResolutionSinceFirstCall()
    {
        static auto start_timepoint = std::chrono::steady_clock::now();
        auto now_milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>
            (std::chrono::steady_clock::now() - start_timepoint).count();
        return now_milliseconds;
    }
}