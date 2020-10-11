//
// Created by Eli Eli on 2020-10-07.
//

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

        void ExecuteCommand(const std::string & cmdName, const char * params = nullptr, const uint8_t numParams = 0) const {
            dbg::Args::Inst().SetArgs(params, numParams);

            for (const auto & menu : m_Menus) {
                menu.ExecuteCommand(cmdName);
            }
        }

    };
}


#endif //DEBUG_MENU_DBGMAINMENU_H
