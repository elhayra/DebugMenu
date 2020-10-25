

#ifndef DEBUG_MENU_DBGPARAM_H
#define DEBUG_MENU_DBGPARAM_H


#include "DbgPrintableEntity.h"

#include <string>
#include <vector>
#include <iostream>

namespace dbg {

    class Option : public PrintableEntity {

    private:
        const std::string m_Value;

    public:
       Option(const std::string & value, const std::string & name, const std::string & descp = "") :
            m_Value{value},
           PrintableEntity(name, descp){ }
        void Print(const size_t maxWidth = 0) const override {
           std::cout << '[' + m_Value + "] <" + m_Name + '>';
           if ( ! m_Description.empty() ) {
               std::cout << " - " + m_Description;
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
                    {  }

        void Print(const size_t maxWidth = 0) const override {
            std::cout << '<' + m_Name + "> - " + m_Description + '\n';
            if (m_Options.empty()) {return;}
            for (const auto option : m_Options) {
                option.Print();
                std::cout << std::endl;
            }
        }
    };

}


#endif //DEBUG_MENU_DBGPARAM_H
