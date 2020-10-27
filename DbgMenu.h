
#ifndef DEBUG_MENU_DBGMENU_H
#define DEBUG_MENU_DBGMENU_H

#include "DbgSubMenu.h"
#include "DbgPrintableEntity.h"
#include "DbgPrintSettings.h"
#include "DbgUtil.h"

#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

namespace dbg {


    class Menu : public PrintableEntity {
    private:
        std::vector<SubMenu> m_SubMenus;




        void _PrintMenuHeader(const size_t maxWidth) const {

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

        void _PrintMenuFooter(const size_t maxWidth) const {
            std::cout << std::string(maxWidth, DBG_MENU_BORDER) << '\n';
            std::cout << std::string(maxWidth, DBG_MENU_BORDER) << '\n';
        }

    public:
        Menu(const std::string & name,
             const std::string & description,
             const std::vector<SubMenu> & subMenus) :
             PrintableEntity(name, description),
             m_SubMenus{subMenus}
             {
                 std::string subMenuName = util::_GetFirstNonUniqueElement(m_SubMenus);
                 if ( ! subMenuName.empty() ) {
                     printf("error: %s | Sub-Menu name %s already exist\n", __PRETTY_FUNCTION__, subMenuName.c_str()); // todo: RT_
                 }
                m_Width = GetSubElementWithMaxWidth();
             }

        /**
         * Execute command
         * @param cmdName - the name of the command to execute (must be unique)
         * @return - true if found command to execute, false otherwise
         */
        bool ExecuteCommand(const std::string & cmdName, const uint8_t numParams) const {
            if (m_SubMenus.empty()) {
                return false;
            }
            for (const auto subMenu : m_SubMenus) {
                const auto execRes = subMenu.ExecuteCommandIfExist(cmdName, numParams);
                if (execRes != SubMenu::eExecResult::NOT_FOUND) {
                    // in any case we found the command, stop searching for it and return
                    return true;
                }
            }
            return false;
        }

        /**
         * Print command description (help)
         * @param cmdName - name of the command
         * @return - true if found command, false otherwise
         */
        bool PrintCommandHelp(const std::string & cmdName) const {
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

        size_t GetSubElementWithMaxWidth() const override {
            // find sub menu with biggest width
            const auto subMenuWithMaxWidth = std::max_element(m_SubMenus.begin(), m_SubMenus.end(),
                  [](const SubMenu& subMenu1, const SubMenu& subMenu2) {
                      return subMenu1.Width() < subMenu2.Width();
                  }
            );

            return subMenuWithMaxWidth->Width();
        }

        void Print(const size_t maxWidth) const override {

            _PrintMenuHeader(maxWidth);

            std::for_each(m_SubMenus.begin(), m_SubMenus.end(), [&](const SubMenu& submenu){ submenu.Print(maxWidth); });

            _PrintMenuFooter(maxWidth);

            std::cout << std::endl;
        }

    };

}

#endif //DEBUG_MENU_DBGMENU_H
