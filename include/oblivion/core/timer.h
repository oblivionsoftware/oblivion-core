/* Copyright (c) 2013 Oblivion Software */

#ifndef _OBLIVION_CORE_TIMER_H_
#define _OBLIVION_CORE_TIMER_H_

#include <chrono>

#include <oblivion/core/base.h>
#include <oblivion/core/types.h>

namespace oblivion {

    /**
     * A high resolution timer.
     */
    class OB_CORE_API Timer {

    public:

        /**
         * Initializes the timer.
         */
        Timer();

        /**
         * Resets the timer.
         */
        void reset();

        /**
         * Gets the number of elapsed seconds since the timer was initialized or reset.
         * @return The number of seconds.
         */
        real32 elapsedTime();

    private:

        std::chrono::high_resolution_clock::time_point start_;

    };

}

#endif /* _OBLIVION_CORE_TIMER_H_ */
