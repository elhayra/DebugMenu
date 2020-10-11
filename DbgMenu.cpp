//
// Created by Eli Eli on 2020-10-07.
//

#include "DbgMenu.h"



namespace dbg {


    std::ostream &operator<<(std::ostream &output, const Menu & menu) {
        output << menu.m_DisplayStr << '\n';
        return output;
    }

}
