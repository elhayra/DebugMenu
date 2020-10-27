
#include "DbgParamsParser.h"

#include <string>
#include <iostream>
#include <sstream>
#include <limits>




/*
 * Get next available argument if available. Otherwise return "null" chosen value
 */

//todo: add to the error the text: failed to parse param. make sure that you provided enough params in command line
#define __DBG_GET_ARGS_AND_CHECK__(ret_val)\
    std::istringstream ss(Args::Inst().GetNext());\
    do {\
        if (ss.str().empty()) {\
            printf("error: %s\n", __PRETTY_FUNCTION__);\
            return ret_val;\
        }\
    } while (0)

namespace dbg {

namespace {

    /**
     *
     * @tparam ValueT - numberic value type
     * @tparam BoundT - numeric boundary type
     * @param value - numeric value to check
     * @return true if number within numeric boundaries included [min, max]
     */
    template <typename ValueT, typename BoundT>
    bool WithinNumericBoundsIncluded(const ValueT value) {
        return WithinBoundsIncluded(value, std::numeric_limits<BoundT>().min(), std::numeric_limits<BoundT>().max());
    }

    /**
     *
     * @tparam T - numberic value type
     * @tparam S - numeric boundary type
     * @param hexMode - parse number as hex
     * @return T - parsed numeric value
     */
    template <typename T, typename S>
    T GetNumberParam() {
        __DBG_GET_ARGS_AND_CHECK__(0);
        T res = 0;
        const auto & str = ss.str();
        const bool hexPrefix = (str.size() > 2) && (str[0] == '0') && (str[1] == 'x');
        if (hexPrefix) { // if string starts with 0x prefix, ignore it
            ss.ignore(2);
            ss >> std::hex >> res;
            ss >> std::dec;
        } else {
            ss >> res;
        }
        return WithinNumericBoundsIncluded<T, S>(res) ? res : 0;
    }
}

    uint8_t GetNumOfParams() { return Args::Inst().GetNumOfParams(); }

    template <typename T>
    T GetParam() { printf("error: %s\n", __PRETTY_FUNCTION__);/* todo: print error - type not implemented */ }

    /** INTEGERS **/

    template <>
    uint8_t GetParam<uint8_t>() { return GetNumberParam<uint64_t, uint8_t>(); }

    template <>
    uint16_t GetParam<uint16_t>() { return GetNumberParam<uint64_t, uint16_t>(); }

    template <>
    uint32_t GetParam<uint32_t>() { return GetNumberParam<uint64_t, uint32_t>(); }

    template <>
    uint64_t GetParam<uint64_t>() { return GetNumberParam<uint64_t, uint64_t>(); }

    template <>
    int8_t GetParam<int8_t>()   { return GetNumberParam<int64_t, int8_t>(); }

    template <>
    int16_t GetParam<int16_t>() { return GetNumberParam<int64_t, int16_t>(); }

    template <>
    int32_t GetParam<int32_t>() { return GetNumberParam<int64_t, int32_t>(); }

    template <>
    int64_t GetParam<int64_t>() { return GetNumberParam<int64_t, int64_t>(); }

    /** FLOATING POINTS **/

    template <>
    float GetParam<float>() { return GetNumberParam<int64_t, float>();}

    template <>
    double GetParam<double>() { return GetNumberParam<int64_t, double>(); }

    /** BOOLEAN **/

    template <>
    bool GetParam<bool>() {
        __DBG_GET_ARGS_AND_CHECK__(false);
        return static_cast<bool>(ss.str()[0]);
    }

    /** STRINGS **/

    template <>
    char GetParam<char>() {
        __DBG_GET_ARGS_AND_CHECK__('\0');
        return ss.str()[0];
    }

    template <>
    std::string GetParam<std::string>() {
        __DBG_GET_ARGS_AND_CHECK__("");
        return ss.str();
    }

}