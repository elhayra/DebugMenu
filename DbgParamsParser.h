
#ifndef DEBUG_MENU_DBGPARAMSPARSER_H
#define DEBUG_MENU_DBGPARAMSPARSER_H


#include "DbgArgs.h"

#include <cstdint>
#include <vector>

//todo: write macros to assert params boundaries and print auto error with numbers in case failed

namespace dbg {

    struct hex {
        int64_t Value {0};
        hex() = default;
        hex(const int64_t value) : Value{value} { }
    };

    template <typename T>
    T GetParam();

    template <typename T, typename B>
    bool WithinBoundsNotIncluded(const T value, const B lowerBound, const B upperBound) {
        return ((value > lowerBound) && (value < upperBound));
    }

    template <typename T, typename B>
    bool WithinBoundsIncluded(const T value, const B lowerBound, const B upperBound) {
        return ((value >= lowerBound) && (value <= upperBound));
    }

    template <typename T>
    bool IsOneOf(const T value, const std::vector<T> & vec) {
        return std::find(vec.begin(), vec.end(), value);
    }
}

#endif //DEBUG_MENU_DBGPARAMSPARSER_H



