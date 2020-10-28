

#ifndef DEBUG_MENU_DBGMAINMENU_H
#define DEBUG_MENU_DBGMAINMENU_H

#include "DbgMenu.h"
#include "DbgPrintableEntity.h"

#include <vector>

namespace dbg {
    class MainMenu : public PrintableEntity{
    private:
        std::vector<Menu> m_Menus;

        MainMenu(const std::string & name,
                 const std::string & description);

        ~MainMenu() = default;

    public:
        MainMenu(MainMenu const &) = delete;
        MainMenu(MainMenu const &&) = delete;
        MainMenu& operator=(MainMenu const &) = delete;
        MainMenu& operator=(MainMenu const &&) = delete;

        static MainMenu & Instance();

        /**
         * Add new menu and rebuild all menus based on new max width
         * @param menu
         */
        void AddMenu(const Menu & menu);

        void ExecuteCommand(const std::string & cmdName, const char * params, const uint8_t numParams) const ;

        void PrintCommandHelp(const std::string& cmdName);

        void Print(const size_t maxWidth = 0) const override ;

    };
}


#endif //DEBUG_MENU_DBGMAINMENU_H
