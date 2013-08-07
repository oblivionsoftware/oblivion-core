/* Copyright (c) 2013 Oblivion Software */

#ifndef _OBLIVION_CORE_RANDOM_H_
#define _OBLIVION_CORE_RANDOM_H_

#include <oblivion/core/base.h>
#include <oblivion/core/types.h>

namespace oblivion {

    /**
     * Random number generator.
     */
    class OB_CORE_API Random {

    public:

        /**
         * Initializes the random number generator seeded with the current time.
         */
        Random();

        /**
         * Initializes the random number generator with a seed.
         * @param seed The random seed.
         */
        Random(int32 seed);

        /**
         * Gets the next integer in the random sequence. [1 - 2^31)
         * @return A random integer.
         */
        int32 next();

        /**
         * Gets the next integer in the range [0, rangeEnd).
         * @param rangeEnd The exclusive maximum of the range.
         * @return A random integer in the range [0, rangeEnd).
         */
        int32 nextRange(int32 rangeEnd);

        /**
         * Gets a random bool value.
         * @return True or false, randomly.
         */
        bool nextBool();

        /**
         * Gets the next real value in the range [0, 1]
         * @return A random real in the range [0, 1]
         */
        real32 nextReal();

    private:

        /**
         * Initializes the random number generator with the specified seed.
         * @param seed The random seed.
         */
        void init(int32 seed);

        /**
         * Generates the numbers for the mersenne twister.
         */
        void generateNumbers();

        int32 mt_[624];

        int32 index_;

    };

}

#endif /* _OBLIVION_CORE_RANDOM_H_ */
