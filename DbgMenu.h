
#ifndef DEBUG_MENU_DBGMENU_H
#define DEBUG_MENU_DBGMENU_H

#include "DbgSubMenu.h"
#include "DbgPrintableEntity.h"


#include <string>
#include <vector>


namespace dbg {


    class Menu : public PrintableEntity {
    private:
        std::vector<SubMenu> m_SubMenus;

        void _PrintMenuHeader(const size_t maxWidth) const;

        void _PrintMenuFooter(const size_t maxWidth) const;

    public:
        Menu(const std::string & name,
             const std::string & description,
             const std::vector<SubMenu> & subMenus);

        /**
         * Execute command
         * @param cmdName - the name of the command to execute (must be unique)
         * @return - true if found command to execute, false otherwise
         */
        bool HandleCommand(const std::string &cmdName, const uint8_t numParams) const;

        /**
         * Print command description (help)
         * @param cmdName - name of the command
         * @return - true if found command, false otherwise
         */
        bool PrintCommandHelp(const std::string & cmdName) const;

        size_t GetSubElementWithMaxWidth() const override;

        void Print(const size_t maxWidth) const override;

    };

}

#endif //DEBUG_MENU_DBGMENU_H
