

#ifndef DEBUG_MENU_DBGSUBMENU_H
#define DEBUG_MENU_DBGSUBMENU_H


#include "DbgCommand.h"
#include "DbgPrintableEntity.h"






namespace dbg {


    class SubMenu : public PrintableEntity{
    private:

        std::vector<Command> m_Commands;

        void _BuildDisplayString() override;

        void _AddSubMenuHeader(std::stringstream & ss);

        void _AddSubMenuFooter(std::stringstream & ss);

    public:
        SubMenu(const std::string & name,
             const std::string & description,
             const std::vector<Command> & cmds);

        /**
         * Execute command if it exist in this sub menu
         * @param cmdName - command name to execute
         * @return true if command name found in this sub menu, false otherwise
         */
        bool ExecuteCommandIfExist(const std::string & cmdName) const ;
    };

}









#endif //DEBUG_MENU_DBGSUBMENU_H
