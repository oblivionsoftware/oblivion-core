/* Copyright (c) 2013 Oblivion Software */

#include <gtest/gtest.h>

#include <thread>

#include <oblivion/core/timer.h>

namespace oblivion {

/*****************************************************************************/

TEST(TimerTest, ElapsedTime) {
    Timer timer;

    std::this_thread::sleep_for(std::chrono::seconds(1));

    EXPECT_LT(1.0f, timer.elapsedTime());
    EXPECT_GT(1.5f, timer.elapsedTime());
}

/*****************************************************************************/

}
