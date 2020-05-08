#pragma once

#include <chrono>

namespace Util
{
    ///benchmark snippet from https://stackoverflow.com/questions/1861294/how-to-calculate-execution-time-of-a-code-snippet-in-c
    class Timer
    {
    public:
        Timer() : beg_(clock_::now()) {}
        void reset() { beg_ = clock_::now(); }
        double elapsed() const {
            return std::chrono::duration_cast<second_>
                (clock_::now() - beg_).count();
        }

    private:
        using clock_ = std::chrono::high_resolution_clock;
        using second_ = std::chrono::duration<double, std::ratio<1>>;
        std::chrono::time_point<clock_> beg_;
    };
}
