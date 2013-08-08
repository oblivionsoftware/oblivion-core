/* Copyright (c) 2013 Oblivion Software */

#ifndef _OBLIVION_CORE_NON_COPYABLE_H_
#define _OBLIVION_CORE_NON_COPYABLE_H_

namespace oblivion {

    /**
     * Base class for objects that can't be copied.
     * This causes a compilation error if a derived class is copied or assigned.
     */
    class NonCopyable {

    protected:

        NonCopyable() { }
        virtual ~NonCopyable() { }

    private:

        NonCopyable(const NonCopyable& other);

        NonCopyable& operator =(const NonCopyable& other);

    };

}

#endif /* _OBLIVION_CORE_NON_COPYABLE_H_ */
