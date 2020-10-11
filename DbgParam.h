

#ifndef DEBUG_MENU_DBGPARAM_H
#define DEBUG_MENU_DBGPARAM_H


#include "DbgNamedEntity.h"

#include <string>
#include <vector>


namespace dbg {

    struct option_t : public NamedEntity {
        const std::string Value;
       option_t(const std::string & value, const std::string & name, const std::string & descp = "") :
            Value{value},
           NamedEntity(name, descp){ }
    };

    class Param : public NamedEntity {
    private:
        const std::vector<option_t> m_Options;

    public:
        Param(const std::string & name,
                const std::string & description,
                const std::vector<option_t> & options = std::vector<option_t>()) :
                    NamedEntity(name, description),
                    m_Options{options}
                    { }
    };

}


#endif //DEBUG_MENU_DBGPARAM_H
//    AddParam(
//        "param name",
//        "descp",
//        {
//            "option 1 for that param",
//            "option 2 for that param",
//            "option 3 for that param",
//            ...
//        }
//    )