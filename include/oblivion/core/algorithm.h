/* Copyright (c) 2013 Oblivion Software */

#ifndef _OBLIVION_CORE_ALGORITHM_H_
#define _OBLIVION_CORE_ALGORITHM_H_

#include <algorithm>
#include <functional>
#include <map>
#include <string>

namespace oblivion {

    /**
     * Performs the specified function for each element of a container.
     * @param container The container.
     * @param f The function to perform.
     */
    template <typename Container, typename UnaryFunction>
    void for_each(Container& container, UnaryFunction f);

    /**
     * Wraps std::find_if for an entire container.
     * @param container The container.
     * @param p The predicate.
     */
    template <typename Container, typename Predicate>
    typename Container::iterator find_if(Container& container, Predicate p);

    /**
     * Wraps std::find_if for an entire constant container.
     * @param container The container.
     * @param p The predicate.
     */
    template <typename Container, typename Predicate>
    typename Container::const_iterator find_if(const Container& container, Predicate p);

    /**
     * Selects the first element of a pair.
     */
    template <typename Pair>
    struct select_first {
        typename Pair::first_type operator ()(const Pair& pair);
    };

    /**
     * Selects the second element of a pair.
     */
    template <typename Pair>
    struct select_second {
        typename Pair::second_type operator ()(const Pair& pair);
    };

    /**
     * Copies the map keys to an output iterator.
     * @param map The input map.
     * @param out The output iterator.
     */
    template <typename Map, typename OutputIterator>
    void map_keys(const Map& map, OutputIterator out);

    /**
     * Copies the map values to an output iterator.
     * @param map The input map.
     * @param out The output iterator.
     */
    template <typename Map, typename OutputIterator>
    void map_values(const Map& map, OutputIterator out);

    /**
     * Erases a value from the specified vector using the erase-remove idiom.
     * @param v The vector with the elements to remove.
     * @param value The value to remove from the vector.
     */
    template <typename T>
    void erase(std::vector<T>& v, const T& value);

    /**
     * Erases values from the vector that match the specified predicate.
     * @param v The vector with the elements to remove.
     * @param predicate The predicate.
     */
    template <typename T, typename Predicate>
    void erase_if(std::vector<T>& v, Predicate predicate);

    /**
     * Gets whether or not a vector contains the specified value.
     * @param v The vector to check.
     * @param value The value to check for.
     * @return True if v contains value, false otherwise.
     */
    template <typename T>
    bool contains(const std::vector<T>& v, const T& value);

}

#include <oblivion/core/algorithm_inl.h>

#endif /* _OBLIVION_CORE_ALGORITHM_H_ */
