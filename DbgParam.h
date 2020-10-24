

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
       Option(const std::string & value, const std::string & name, const std::string & descp = "") :
            m_Value{value},
           PrintableEntity(name, descp){ _BuildDisplayString(); }
        void _BuildDisplayString() override {
           m_DisplayStr = '[' + m_Value + "] <" + m_Name + '>';
           if ( ! m_Description.empty() ) {
               m_DisplayStr += " - " + m_Description;
           }
       }
    };

    class Param : public PrintableEntity {
    private:
        const std::vector<Option> m_Options;

    public:
        Param(const std::string & name,
                const std::string & description,
                const std::vector<Option> & options = std::vector<Option>()) :
                    PrintableEntity(name, description),
                    m_Options{options}
                    { }

        void _BuildDisplayString() override {
            m_DisplayStr = '<' + m_Name + "> - " + m_Description + '\n';
            if (m_Options.empty()) {return;}
            for (const auto option : m_Options) {
                m_DisplayStr += '\t' + option.Display() + '\n';
            }
        }
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