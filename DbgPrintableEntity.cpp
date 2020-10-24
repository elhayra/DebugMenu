//
// Created by Eli Eli on 2020-10-24.
//

#include "DbgPrintableEntity.h"

namespace dbg {

    std::ostream &operator<<(std::ostream & output, const dbg::PrintableEntity& printable) {
        output << printable.Display();
        return output;
    }
}
