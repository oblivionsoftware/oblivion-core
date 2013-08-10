/* Copyright (c) 2013 Oblivion Software */

#ifndef _OBLIVION_CORE_SINGLETON_H_
#define _OBLIVION_CORE_SINGLETON_H_

#include <cstdint>

#include <oblivion/core/non_copyable.h>

namespace oblivion {

    /**
     * Base class for singleton classes.
     */
    template <typename T>
    class Singleton : NonCopyable {

    public:

        /**
         * Gets A pointer to this singleton instance.
         * @return A pointer to the instance.
         */
        static T* get() {
            static T instance;
            return &instance;
        }

    };

}

#endif /* _OBLIVION_CORE_SINGLETON_H_ */
