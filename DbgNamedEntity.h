

#ifndef DEBUG_MENU_DBGNAMEDENTITY_H
#define DEBUG_MENU_DBGNAMEDENTITY_H

#include <string>

namespace dbg {

    class NamedEntity {
    protected:
        const std::string m_Name;
        const std::string m_Description;


        NamedEntity(const std::string & name,
              const std::string & description) :
              m_Name{name},
              m_Description{description} {  }


        std::string Name() const { return m_Name; }
        std::string Description() const { return m_Description; }

    };

}

#endif //DEBUG_MENU_DBGNAMEDENTITY_H
