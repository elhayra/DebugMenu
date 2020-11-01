//
// Created by Eli Eli on 2020-10-24.
//

#include "DbgPrintableEntity.h"

namespace dbg {

    PrintableEntity::PrintableEntity(const std::string & name,
                    const std::string & description) :
            m_Name{name},
            m_Description{description}
    {
        _VerifyName();
    }

    size_t PrintableEntity::Width() const {
        if (m_Width == 0) { // not initialized
            printf("error: %s\n", __PRETTY_FUNCTION__);
        }
        return m_Width;
    }

    void PrintableEntity::_VerifyName() {
        if (m_Name.empty()) {
            printf("error name can't be blank %s\n", __PRETTY_FUNCTION__); //todo: rt_err
        }
    }
}