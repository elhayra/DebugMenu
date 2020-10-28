

#ifndef DEBUG_MENU_DBGPARAM_H
#define DEBUG_MENU_DBGPARAM_H


#include "DbgPrintableEntity.h"

#include <string>
#include <vector>

namespace dbg {

    class Option : public PrintableEntity {

    private:
        const std::string m_Value;

    public:
       Option(const std::string & value, const std::string & name, const std::string & descp = "") ;
        void Print(const size_t maxWidth = 0) const override ;
    };

    class Param : public PrintableEntity {
    private:
        const std::vector<Option> m_Options;

    public:
        Param(const std::string & name,
                const std::string & description,
                const std::vector<Option> & options = std::vector<Option>());

        void Print(const size_t maxWidth = 0) const override ;
    };

}


#endif //DEBUG_MENU_DBGPARAM_H
