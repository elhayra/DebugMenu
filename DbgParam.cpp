

#include "DbgParam.h"


#include <iostream>


namespace dbg {

    /** OPTION **/


    Option::Option(const std::string & value, const std::string & name, const std::string & descp) :
            m_Value{value},
            PrintableEntity(name, descp){ }

    void Option::Print(const size_t maxWidth) const {
        std::cout << '[' + m_Value + "] <" + m_Name + '>';
        if ( ! m_Description.empty() ) {
            std::cout << " - " + m_Description;
        }
    }


    /** PARAM **/


    Param::Param(const std::string & name,
          const std::string & description,
          const std::vector<Option> & options) :
            PrintableEntity(name, description),
            m_Options{options}
    {  }


    Param::Param(const param_data_t & paramData) :
            PrintableEntity(paramData.Name, paramData.Description),
            m_Options{paramData.Options}
    {  }


    void Param::Print(const size_t maxWidth) const {
        std::cout << "\t<" + m_Name + "> - " + m_Description + '\n';
        if (m_Options.empty()) {return;}
        for (const auto option : m_Options) {
            std::cout << "\t\t";
            option.Print();
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

}