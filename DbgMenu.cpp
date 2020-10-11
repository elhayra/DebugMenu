

#include "DbgMenu.h"



namespace dbg {


    std::ostream &operator<<(std::ostream &output, const Menu & menu) {
        output << menu.m_DisplayStr << '\n';
        return output;
    }

}
