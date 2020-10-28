

#ifndef DEBUG_MENU_DBGCOMMAND_H
#define DEBUG_MENU_DBGCOMMAND_H

#include "DbgParam.h"

#include <string>
#include <vector>
#include <functional>
#include <iostream>
#include <sstream>
#include <chrono>

#include "DbgArgs.h"
#include "DbgPrintableEntity.h"


namespace dbg {

    struct cmd_ret_t {
        bool Success;
        std::string Message;
        cmd_ret_t(const bool success, const std::string& msg="") :
            Success{success}, Message{msg} { }
    };

    class Command : public PrintableEntity {
    private:
        static uint16_t m_IdGen;
        const uint16_t m_Id;
        std::function<cmd_ret_t()> m_Callback;
        const std::vector<Param> m_Params;

        void _UpdateWidthByName() { m_Width = m_Name.size() + 4; }

    public:
        Command(const std::string &name,
                const std::string &description,
                const std::vector<Param> &params,
                const std::function<cmd_ret_t()> &callback);

        Command(const Command& other);

        Command(const Command&& other) = delete;

        uint16_t Id() const { return m_Id; }

        size_t NumOfParams() const { return m_Params.size(); }

        void AddSubMenuNameAsPrefix(const std::string & subMenuName);

        void Print(const size_t maxWidth = 0) const override ;

        void PrintHelp() const ;

        bool Run(const bool multiMeasure) const ;

    };


} // end of dbg



#endif //DEBUG_MENU_DBGCOMMAND_H


