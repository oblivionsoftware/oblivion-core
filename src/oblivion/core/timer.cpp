/* Copyright (c) 2013 Oblivion Software */

#include <oblivion/core/timer.h>

namespace oblivion {

/*****************************************************************************/

Timer::Timer() {
    reset();
}

/*****************************************************************************/

void Timer::reset() {
    start_ = std::chrono::high_resolution_clock::now();
}

/*****************************************************************************/

real32 Timer::elapsedTime() {
    auto now = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(now - start_).count() / 1000.0f;
}

/*****************************************************************************/

}
