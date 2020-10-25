

#ifndef DEBUG_MENU_DBGMAINMENU_H
#define DEBUG_MENU_DBGMAINMENU_H

#include "DbgMenu.h"
#include "DbgArgs.h"
#include "DbgPrintableEntity.h"

#include <vector>
#include <algorithm>

namespace dbg {
    class MainMenu : public PrintableEntity{
    private:
        std::vector<Menu> m_Menus;

        MainMenu(const std::string & name,
                 const std::string & description) :
                 PrintableEntity{name, description} { }

        ~MainMenu() = default;




    public:
        MainMenu(MainMenu const &) = delete;
        MainMenu(MainMenu const &&) = delete;
        MainMenu& operator=(MainMenu const &) = delete;
        MainMenu& operator=(MainMenu const &&) = delete;

        static MainMenu & Instance() {
            static MainMenu instance{"Main Menu", "Main Menu of the New Debug Menu"};
            return instance;
        }

        /**
         * Add new menu and rebuild all menus based on new max width
         * @param menu
         */
        void AddMenu(const Menu & menu) {
            m_Menus.push_back(menu);
        }

        void ExecuteCommand(const std::string & cmdName, const char * params, const uint8_t numParams) const {
            dbg::Args::Inst().SetArgs(params, numParams);

            for (const auto & menu : m_Menus) {
                if (menu.ExecuteCommand(cmdName, numParams)) {
                    return;
                }
            }
        }

        void PrintCommandHelp(const std::string& cmdName) {
            for (const auto & menu : m_Menus) {
                if (menu.PrintCommandHelp(cmdName)) {
                    return;
                }
            }
        }


        void Print(const size_t maxWidth = 0) const override {
            std::stringstream ss;

            // find the widest menu
            const auto menuWithMaxWidth = std::max_element(m_Menus.begin(), m_Menus.end(),
                                                           [](const Menu& menu1, const Menu& menu2) {
                                                               return menu1.Width() < menu2.Width();
                                                           }
            );

            for (auto & menu : m_Menus) {
                menu.Print(menuWithMaxWidth->Width());
            }
        }


    };
}


#endif //DEBUG_MENU_DBGMAINMENU_H
