/* Copyright (c) 2013 Oblivion Software */

#ifndef _OBLIVION_CORE_PROPERTIES_H_
#define _OBLIVION_CORE_PROPERTIES_H_

#include <string>
#include <unordered_map>

#include <oblivion/core/base.h>
#include <oblivion/core/types.h>

namespace oblivion {

    /**
     * Storage for name/value pairs.
     */
    typedef std::unordered_map<std::string, std::string> PropertyMap;

    /**
     * The properties class encapsulates a set of string/value pairs
     * with support for reading and writing to files.
     */
    class OB_CORE_API Properties {

    public:

        /**
         * Constant iterator type.
         */
        typedef PropertyMap::const_iterator const_iterator;

        /** 
         * Constructs an empty set of properties.
         */
        Properties();

        /**
         * Constructs a set of properties by loading from the specified path.
         * @param path The path to the file to load.
         * @throw Exception if the properties file cannot be loaded.
         */
        explicit Properties(const std::string& path);

        /**
         * Sets the value of the specified property.
         * @param name The name of the property.
         * @param value The value of the property.
         */
        void setProperty(const std::string& name, const std::string& value);

        /**
         * Sets the value of the specified property to the string representation of a value.
         * @param name The name of the property.
         * @param value The value to set.
         */
        template <typename T>
        void set(const std::string& name, const T& value);

        /**
         * Gets the value of a property.
         * @param name The name of the property to get.
         * @param defaultValue The value to return if the property doesn't exist.
         * @return The value of the property if one exists, or defaultValue otherwise.
         */
        const std::string& getProperty(const std::string& name, const std::string& defaultValue = "");

        /**
         * Gets the value of a property, converting from a string representation.
         * @param name The value of the property to get.
         * @param defaultValue the value to return if the property doesn't exist.
         * @return The value of the property if one exists, or defaultValue otherwise.
         */
        template <typename T>
        T get(const std::string& name, const T& defaultValue = T());

        /**
         * Gets whether or not this properties collection contains a value for the specified property name.
         * @param name The name of the property to look for.
         * @return True if there is a property entry, false otherwise.
         */
        bool contains(const std::string& name);

        /**
         * Saves the set of properties to a file.
         * @param path The path to the file to write.
         * @throw Exception if the properties file cannot be saved.
         */
        void save(const std::string& path);

        /**
         * Loads the set of properties from a file.
         * @param path The path to the file to read.
         * @throw Exception if the properties file cannot be loaded.
         */
        void load(const std::string& path);

        /**
         * Gets the first iterator to the property map.
         * @return The iterator.
         */
        const_iterator begin() const;

        /**
         * Gets the ending iterator to the property map.
         * @return The last iterator.
         */
        const_iterator end() const;

        /**
         * Gets the number of properties in the collection.
         * @return The number of properties in the collection.
         */
        int32 size() const;

        /**
         * Gets whether or not the property collection is empty.
         * @return True if the collection is empty, false otherwise.
         */
        bool empty() const;

        /**
         * Removes all elements from this collection.
         */
        void clear();

    private:

        PropertyMap properties_;

    };

}

#include <oblivion/core/properties_inl.h>

#endif /* _OBLIVION_CORE_PROPERTIES_H_ */
