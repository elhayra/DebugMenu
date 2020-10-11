//
// Created by Eli Eli on 2020-10-07.
//

#include "DbgSubMenu.h"

namespace dbg {

    std::ostream &operator<<(std::ostream & output, const dbg::SubMenu& subMenu) {
        output << '\n' << subMenu.m_DisplayStr << '\n';
        return output;
    }

}