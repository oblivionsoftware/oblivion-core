/* Copyright (c) 2013 Oblivion Software */

#include <oblivion/core/random.h>

#include <ctime>
#include <limits>

namespace oblivion {

/*****************************************************************************/

Random::Random() {
    auto seed = static_cast<int32>(time(nullptr));
    init(seed); 
}

/*****************************************************************************/

Random::Random(int32 seed) {
    init(seed);
}

/*****************************************************************************/

int32 Random::next() {
    if (index_ == 0) {
        generateNumbers();
    }

    int32 y = mt_[index_];
    y = y ^ (y >> 11);
    y = y ^ ((y << 7) & 0x9d2c5680);
    y = y ^ ((y << 15) & 0xefc60000);
    y = y ^ (y >> 18);

    index_ = (index_ + 1) % 624;

    return y;
}

/*****************************************************************************/

int32 Random::nextRange(int32 rangeEnd) {
    return next() % rangeEnd;
}

/*****************************************************************************/

bool Random::nextBool() {
    return (next() % 2) == 0;
}

/*****************************************************************************/

real32 Random::nextReal() {
    return static_cast<real32>(next() / std::numeric_limits<int32>::max());
}

/*****************************************************************************/

void Random::init(int32 seed) {
    index_ = 0;
    mt_[0] = seed;

    for (int i = 1; i < 624; ++i) {
        mt_[i] = (0x6c078965 * (mt_[i - 1] ^ (mt_[i - 1] >> 30))) + i;
    }
}

/*****************************************************************************/

void Random::generateNumbers() {
    for (int32 i = 0; i < 624; ++i) {
        int32 y = (mt_[i] & 0x80000000) + (mt_[(i + 1) % 624] & 0x7fffffff);
        mt_[i] = mt_[(i + 397) % 624] ^ (y >> 1);
        
        if ((y % 2) != 0) {
            mt_[i] = mt_[i] ^ 0x9908b0df;
        }
    }
}

/*****************************************************************************/

}
