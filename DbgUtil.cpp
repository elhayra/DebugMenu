//
// Created by Eli Eli on 2020-10-28.
//


#include "DbgUtil.h"

#include <string>
#include <algorithm>


namespace dbg {
    namespace util {
        std::string StrToUpperCase(const std::string& str) {
            std::string copyStr = str;
            std::transform(copyStr.begin(), copyStr.end(),copyStr.begin(), ::toupper);
            return copyStr;
        }
    }
}