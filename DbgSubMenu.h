

#ifndef DEBUG_MENU_DBGSUBMENU_H
#define DEBUG_MENU_DBGSUBMENU_H


#include "DbgCommand.h"
#include "DbgNamedEntity.h"



//todo: if command already exist, print error
//todo: automatically print command help menu if params are wrong or num of params is wrong
//todo: move includes and impl code  to the right place in cpp file


namespace dbg {


    class SubMenu : public NamedEntity{
    private:

        std::vector<Command> m_Commands;
        std::string m_DisplayStr;
        uint16_t m_Width {0};

        void _BuildPrintStr();

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

        uint16_t GetWidth() const { return m_Width; }

        friend std::ostream &operator<<(std::ostream & output, const dbg::SubMenu& subMenu);
    };

}









#endif //DEBUG_MENU_DBGSUBMENU_H
