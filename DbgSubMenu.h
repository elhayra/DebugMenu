

#ifndef DEBUG_MENU_DBGSUBMENU_H
#define DEBUG_MENU_DBGSUBMENU_H


#include "DbgCommand.h"
#include "DbgPrintableEntity.h"
#include "DbgPrintSettings.h"


#include <array>



namespace dbg {


    class SubMenu : public PrintableEntity{
    private:

        std::vector<Command> m_Commands;

        // hold max command length in each column
        std::array<size_t, DBG_NUM_CMD_IN_ROW> m_ColsMaxWidth {0};

        void _PrintSubMenuHeader(const size_t maxWidth) const ;

        void _PrintSubMenuFooter(const size_t maxWidth) const ;

        void _CalcColsMaxWidths();

        void _AddCommandsNamePrefix();

    public:
        enum class eExecResult {
            FOUND_BUT_FAILED, // found command but execution failed
            FOUND_AND_SUCCEEDED, // found command and execution succeeded
            NOT_FOUND, // command not found in this sub-menu,
            PRE_COND_FAIL // other pre-condition failed
        };

        SubMenu(const std::string & name,
             const std::string & description,
             const std::vector<Command> & cmds);

        /**
         * Execute command if it exist in this sub menu
         * @param cmdName - command name to execute
         * @return eExecResult
         */
        eExecResult ExecuteCommandIfExist(const std::string & cmdName, const uint8_t numParams) const ;

        /**
         * print command help if it exist in this sub menu
         * @param cmdName - command name
         * @return true if command found, false otherwise
         */
        bool PrintCommandHelpIfExist(const std::string & cmdName) const ;

        void Print(const size_t maxWidth) const override;

    };

}









#endif //DEBUG_MENU_DBGSUBMENU_H
