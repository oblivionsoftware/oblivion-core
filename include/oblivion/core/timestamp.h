/* Copyright (c) 2013 Oblivion Software */

#ifndef _OBLIVION_CORE_TIMESTAMP_H_
#define _OBLIVION_CORE_TIMESTAMP_H_

#include <ctime>
#include <iosfwd>
#include <string>

#include <oblivion/core/base.h>
#include <oblivion/core/types.h>

namespace oblivion {

    /**
     * Represents a datetime combination.
     */
    class OB_CORE_API Timestamp {

    public:

        /**
         * Initializes the timestamp to the current time.
         */
        Timestamp();

        /**
         * Gets the IOS8601 standard time representation of this timestamp
         * @return The ISO8601 string. (eg. 2013-08-08T18:34Z)
         */
        std::string iso8601() const;

        /**
         * Formats the timestap with the specified format string.
         * @param format The format string.
         * @return The formatted timestamp. 
         * @see strftime
         */
        std::string format(const std::string& format) const;

        /**
         * Prints the timestamp to an output stream in the standard date/time format.
         * @param os The output stream to print to.
         */
        void print(std::ostream& os) const;

    private:

        std::time_t time_;

    };

    /**
     * Prints a timestamp to an output stream in the standard date/time format.
     * @param os The output stream to write to.
     * @param timestamp The timestamp to print.
     * @return The output stream.
     */
    OB_CORE_API std::ostream& operator <<(std::ostream& os, const Timestamp& timestamp);

}

#endif /* _OBLIVION_CORE_TIMESTAMP_H_ */
