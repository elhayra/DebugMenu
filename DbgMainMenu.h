

#ifndef DEBUG_MENU_DBGMAINMENU_H
#define DEBUG_MENU_DBGMAINMENU_H

#include "DbgMenu.h"
#include "DbgArgs.h"

#include <vector>
#include <algorithm>

namespace dbg {
    class MainMenu {
    private:
        std::vector<Menu> m_Menus;

        MainMenu() = default;
        ~MainMenu() = default;

    public:
        MainMenu(MainMenu const &) = delete;
        MainMenu(MainMenu const &&) = delete;
        MainMenu& operator=(MainMenu const &) = delete;
        MainMenu& operator=(MainMenu const &&) = delete;

        static MainMenu & Instance() {
            static MainMenu instance;
            return instance;
        }

        void AddMenu(const Menu & menu) {
            m_Menus.push_back(menu);
        }

        void ExecuteCommand(const std::string & cmdName, const char * params, const uint8_t numParams) const {
            dbg::Args::Inst().SetArgs(params, numParams);

            for (const auto & menu : m_Menus) {
                if (menu.ExecuteCommand(cmdName)) {
                    return;
                }
            }
        }

        void Print() const {
            std::for_each(m_Menus.begin(), m_Menus.end(), [](const Menu & menu){std::cout << menu;});
        }

    };
}


#endif //DEBUG_MENU_DBGMAINMENU_H
