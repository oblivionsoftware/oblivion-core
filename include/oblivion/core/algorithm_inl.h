/* Copyright (c) 2013 Oblivion Software */

#ifndef _OBLIVION_CORE_ALGORITHM_INL_H_
#define _OBLIVION_CORE_ALGORITHM_INL_H_

namespace oblivion {

/*****************************************************************************/

template <typename Container, typename UnaryFunction>
void for_each(Container& container, UnaryFunction f) {
    std::for_each(std::begin(container), std::end(container), f);
}

/*****************************************************************************/

template <typename Container, typename Predicate>
typename Container::iterator find_if(Container& container, Predicate p) {
    return std::find_if(std::begin(container), std::end(container), p);
}

/*****************************************************************************/

template <typename Container, typename Predicate>
typename Container::const_iterator find_if(const Container& container, Predicate p) {
    return std::find_if(std::begin(container), std::end(container), p);
}

/*****************************************************************************/

template <typename Pair>
typename Pair::first_type select_first<Pair>::operator ()(const Pair& pair) {
    return pair.first;
}

/*****************************************************************************/

template <typename Pair>
typename Pair::second_type select_second<Pair>::operator ()(const Pair& pair) {
    return pair.second;
}

/*****************************************************************************/

template <typename Map, typename OutputIterator>
void map_keys(const Map& map, OutputIterator out) {
    std::transform(std::begin(map), std::end(map), out, select_first<typename Map::value_type>());
}

/*****************************************************************************/

template <typename Map, typename OutputIterator>
void map_values(const Map& map, OutputIterator out) {
    std::transform(std::begin(map), std::end(map), out, select_second<typename Map::value_type>());
}

/*****************************************************************************/

template <typename T>
void erase(std::vector<T>& v, const T& value) {
    v.erase(std::remove(v.begin(), v.end(), value), v.end());
}

/*****************************************************************************/

template <typename T>
bool contains(const std::vector<T>& v, const T& value) {
    return std::find(v.begin(), v.end(), value) != v.end();
}

/*****************************************************************************/

}

#endif /* _OBLIVION_CORE_ALGORITHM_INL_H_ */
