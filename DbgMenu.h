
#ifndef DEBUG_MENU_DBGMENU_H
#define DEBUG_MENU_DBGMENU_H

#include "DbgSubMenu.h"
#include "DbgPrintableEntity.h"


#include <string>
#include <vector>


namespace dbg {

    struct menu_data_t {
        std::string Name;
        std::string Description;
        std::vector<SubMenu> SubMenus;
    };

    class Menu : public PrintableEntity {
    private:
        std::vector<SubMenu> m_SubMenus;

        void _PrintMenuHeader(const size_t maxWidth) const;

        void _PrintMenuFooter(const size_t maxWidth) const;

        void _InitEssentials();

    public:
        Menu(const std::string & name,
             const std::string & description,
             const std::vector<SubMenu> & subMenus);

        Menu(const menu_data_t& menuData);

        bool RunCommandById(const std::string &cmdName, const uint8_t numParams) const;

        bool RunCommandByName(const std::string &cmdName, const uint8_t numParams, const bool benchmark = false) const;

        bool PrintCommandsContainingName(const std::string &cmdName) const;

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
