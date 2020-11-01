

#include "DbgMenu.h"
#include "DbgPrintSettings.h"
#include "DbgUtil.h"


#include <sstream>
#include <algorithm>

namespace dbg {

    Menu::Menu(const std::string & name,
               const std::string & description,
               const std::vector<SubMenu> & subMenus) :
            PrintableEntity(name, description),
            m_SubMenus{subMenus}
    {
        // set min width as a starting point
        m_Width = std::max(m_Description.size(), m_Name.size()) +
                (DBG_MIN_PRE_POST_BORDER_NAME_CHARS * 2);
        if ( ! subMenus.empty() ) {
            std::string existSubMenu = util::_GetFirstNonUniqueElement(m_SubMenus);
            if (existSubMenu != "") {
                printf("error: %s | Sub-Menu name %s already exist\n", __PRETTY_FUNCTION__, existSubMenu.c_str()); // todo: RT_
            } else {
                m_Width = GetSubElementWithMaxWidth();
            }
        }
    }

    void Menu::_PrintMenuHeader(const size_t maxWidth) const {

        // add title top border
        std::cout << std::string(maxWidth, DBG_MENU_BORDER) << '\n';

        // add 2 for space before and after the name
        const size_t subMenuNameLen = m_Name.size() + 2;
        const int subMenuNamePadding = (maxWidth / 2) - (subMenuNameLen / 2);
        if (subMenuNamePadding < 0) {
            printf("error: %s\n", __PRETTY_FUNCTION__); // padding cant be negative
            return;
        }
        if (subMenuNamePadding > 0) {
            // add spaces before sub menu name
            std::cout << std::string(subMenuNamePadding, ' ');
        }

        std::cout << " " <<  m_Name << '\n';

        // add border chars after sub menu name
        std::cout << std::string(maxWidth, DBG_MENU_BORDER) << '\n';

        // add 2 for space before and after the name
        const size_t subMenuDescriptionLen = m_Description.size() + 2;
        const int subMenuDescriptionPadding = (maxWidth / 2) - (subMenuDescriptionLen / 2);
        if (subMenuDescriptionPadding < 0) {
            printf("error: %s\n", __PRETTY_FUNCTION__); // padding cant be negative
            return;
        }
        if (subMenuDescriptionPadding > 0) {
            // add spaces before sub menu name
            std::cout << std::string(subMenuDescriptionPadding, ' ');
        }

        std::cout << " " <<  m_Description << "\n\n";
    }

    void Menu::_PrintMenuFooter(const size_t maxWidth) const {
        std::cout << std::string(maxWidth, DBG_MENU_BORDER) << '\n';
        std::cout << std::string(maxWidth, DBG_MENU_BORDER) << '\n';
    }



    /**
     * Execute command
     * @param cmdName - the name of the command to execute (must be unique)
     * @return - true if found command to execute, false otherwise
     */
    bool Menu::HandleCommand(const std::string &cmdName, const uint8_t numParams) const {
        if (m_SubMenus.empty()) {
            return false;
        }

        std::string cmdNameCopy = cmdName;

        // special commands with prefix
        if (cmdNameCopy.at(0) == '!') { // run command by id
            cmdNameCopy.erase(0, 1); // remove first char ('!') so only id is left
            uint16_t inputCmdId = 0;
            try {
                inputCmdId = std::stoi(cmdNameCopy);// convert string id to number
            } catch (std::invalid_argument) {
                printf("error: %s\n", __PRETTY_FUNCTION__);//todo: print error - conversion to int failed
                return false;
            }
            for (const auto &subMenu : m_SubMenus) {
                if (subMenu.ExecuteCommandById(inputCmdId, numParams)) { return true; }
            }
        } else if (cmdNameCopy.at(0) == '@') { // measure execution time multiple times for better results
            cmdNameCopy.erase(0, 1); // remove first char ('@') so only cmd name is left
            for (const auto &subMenu : m_SubMenus) {
                if (subMenu.ExecuteCommandByName(cmdNameCopy, numParams, true)) { return true; }
            }
        } else if (cmdNameCopy.at(0) == '#') { // find all commands that contain string
            cmdNameCopy.erase(0, 1); // remove first char ('#') so only cmd name is left

            for (const auto &subMenu : m_SubMenus) {
                subMenu.PrintCommandsContainingName(cmdNameCopy);
            }
            return false; // keep looking on other sub-menus
        }

        //standard command
        for (const auto &subMenu : m_SubMenus) {
            if (subMenu.ExecuteCommandByName(cmdNameCopy, numParams)) { return true; }
        }

        return false;
    }

    /**
     * Print command description (help)
     * @param cmdName - name of the command
     * @return - true if found command, false otherwise
     */
    bool Menu::PrintCommandHelp(const std::string & cmdName) const {
        if (m_SubMenus.empty()) {
            return false;
        }
        for (const auto subMenu : m_SubMenus) {
            if (subMenu.PrintCommandHelpIfExist(cmdName)) {
                return true;
            }
        }
        return false;
    }

    size_t Menu::GetSubElementWithMaxWidth() const{
        // find sub menu with biggest width
        const auto subMenuWithMaxWidth = std::max_element(m_SubMenus.begin(), m_SubMenus.end(),
                                                          [](const SubMenu& subMenu1, const SubMenu& subMenu2) {
                                                              return subMenu1.Width() < subMenu2.Width();
                                                          }
        );

        return subMenuWithMaxWidth->Width();
    }

    void Menu::Print(const size_t maxWidth) const {

        _PrintMenuHeader(maxWidth);

        std::for_each(m_SubMenus.begin(), m_SubMenus.end(), [&](const SubMenu& submenu){ submenu.Print(maxWidth); });

        _PrintMenuFooter(maxWidth);

        std::cout << std::endl;
    }


}
