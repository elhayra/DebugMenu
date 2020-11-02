//
// Created by Eli Eli on 2020-10-28.
//

#ifndef DEBUG_MENU_DBGUTIL_H
#define DEBUG_MENU_DBGUTIL_H


#include <vector>
#include <algorithm>
#include "DbgPrintableEntity.h"

namespace dbg {
    namespace util {

        template<class T>
        std::string _GetFirstNonUniqueElement(const std::vector<T> &vec) {
            // create a copy vec that contains only the element names
            std::vector<std::string> strVec;
            strVec.reserve(vec.size());
            for (const auto &elem : vec) {
                strVec.push_back(elem.Name());
            }

            // sort
            auto comparator = [](std::string &str1, std::string &str2) { return str1 < str2; };
            std::sort(strVec.begin(), strVec.end(), comparator);

            // verify
            std::string lastStr = "";
            for (const auto &str : strVec) {
                if (str == lastStr) { // this str is not unique, return it
                    return str;
                } else {
                    lastStr = str;
                }
            }
            return "";
        }


        std::string StrToUpperCase(const std::string &str);
    }
}

#endif //DEBUG_MENU_DBGUTIL_H
