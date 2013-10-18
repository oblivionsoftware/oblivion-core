/* Copyright (c) 2013 Oblivion Software */

#include <gtest/gtest.h>

#include <thread>

#include <oblivion/core/timer.h>

namespace oblivion {

/*****************************************************************************/

TEST(TimerTest, ElapsedTime) {
    Timer timer;

    std::this_thread::sleep_for(std::chrono::milliseconds(200));

    EXPECT_LE(0.1f, timer.elapsedTime());
    EXPECT_GT(0.3f, timer.elapsedTime());
}

/*****************************************************************************/

}
