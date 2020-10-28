//
// Created by Eli Eli on 2020-10-24.
//

#include "DbgPrintableEntity.h"

namespace dbg {

    size_t PrintableEntity::Width() const {
        if (m_Width == 0) { // not initialized
            printf("error: %s\n", __PRETTY_FUNCTION__);
        }
        return m_Width;
    }
}