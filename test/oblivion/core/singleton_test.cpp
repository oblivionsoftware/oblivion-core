/* Copyright (c) 2013 Oblivion Software */

#include <gtest/gtest.h>

#include <oblivion/core/singleton.h>

namespace oblivion {

class A : public Singleton<A> {

    friend class Singleton<A>;

protected:

    A() { }
    ~A() { }

};

/*****************************************************************************/

TEST(SingletonTest, Get) {
    auto a1 = A::get();
    auto a2 = A::get();

    EXPECT_EQ(a1, a2);
}

/*****************************************************************************/

}
