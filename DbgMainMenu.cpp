

#include "DbgMainMenu.h"
#include "DbgArgs.h"
#include "DbgUtil.h"

#include <algorithm>


#define MIN_CMD_NAME_SIZE 2

namespace dbg {


    MainMenu::MainMenu(const std::string & name,
                 const std::string & description) :
                PrintableEntity{name, description} { }



    MainMenu & MainMenu::Instance() {
        static MainMenu instance{"Main Menu", "Main Menu of the New Debug Menu"};
        return instance;
    }

    /**
     * Add new menu and rebuild all menus based on new max width
     * @param menu
     */
    void MainMenu::AddMenu(const Menu & menu) {
        m_Menus.push_back(menu);

        std::string menuName = util::_GetFirstNonUniqueElement(m_Menus);
        if ( ! menuName.empty() ) {
            printf("error: %s | menu name %s already exist\n", __PRETTY_FUNCTION__, menuName.c_str()); // todo: RT_
        }
    }

    void MainMenu::ExecuteCommand(const std::string & cmdName, const char * params, const uint8_t numParams) const {
        if (cmdName.size() < MIN_CMD_NAME_SIZE) {
            printf("error %s\n", __PRETTY_FUNCTION__); // todo: print error command must have at least 2 chars
            return;
        }

        dbg::Args::Inst().SetArgs(params, numParams);

//        for (const auto & menu : m_Menus) {
//            if (menu.HandleCommand(cmdName, numParams)) {
//                return;
//            }
//        }
//        printf("command %s does not exist\n", cmdName.c_str());






        if (m_Menus.empty()) {
            printf("error: no menus are created, can't run any command %s", __PRETTY_FUNCTION__);
            return;
        }

        std::string cmdNameCopy = cmdName;

        const SpecialCmdType cmdType = static_cast<SpecialCmdType>(cmdNameCopy.at(0));

        switch (cmdType) {
            case SpecialCmdType::RUN_BY_ID: {
                cmdNameCopy.erase(0, 1); // remove first char ('!') so only id is left
                for (const auto &menu : m_Menus) {
                    if (menu.RunCommandById(cmdNameCopy, numParams)) { return; }
                }
                printf("command id %s not found %s\n", cmdNameCopy.c_str(), __PRETTY_FUNCTION__);
                break;
            }
            case SpecialCmdType ::MULTI_BENCHMARK: {
                cmdNameCopy.erase(0, 1); // remove first char ('@') so only cmd name is left
                for (const auto &menu : m_Menus) {
                    if (menu.RunCommandByName(cmdNameCopy, numParams, true)) { return; }
                }
                printf("command %s not found %s\n", cmdNameCopy.c_str(), __PRETTY_FUNCTION__);
                break;
            }
            case SpecialCmdType ::SEARCH: {
                cmdNameCopy.erase(0, 1); // remove first char ('#') so only cmd name is left
                for (const auto &menu : m_Menus) {
                    menu.PrintCommandsContainingName(cmdNameCopy);
                }
                break;
            }
            default: { // run command by name
                for (const auto &menu : m_Menus) {
                    if (menu.RunCommandByName(cmdNameCopy, numParams)) { return; }
                }
                printf("command %s not found %s\n", cmdNameCopy.c_str(), __PRETTY_FUNCTION__);
            }
        }

    }

    void MainMenu::PrintCommandHelp(const std::string& cmdName) {
        for (const auto & menu : m_Menus) {
            if (menu.PrintCommandHelp(cmdName)) {
                return;
            }
        }
    }


    void MainMenu::Print(const size_t maxWidth) const {
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


}
