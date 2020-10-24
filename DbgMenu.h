
#ifndef DEBUG_MENU_DBGMENU_H
#define DEBUG_MENU_DBGMENU_H

#include "DbgSubMenu.h"
#include "DbgPrintableEntity.h"
#include "DbgPrintSettings.h"

#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

namespace dbg {


    class Menu : public PrintableEntity {
    private:
        std::vector<SubMenu> m_SubMenus;




        void _AddMenuHeader(std::stringstream &ss, const uint16_t maxWidth) {

            // add title top border
            ss << std::string(maxWidth, DBG_MENU_BORDER) << '\n';

            // add 2 for space before and after the name
            const size_t subMenuNameLen = m_Name.size() + 2;
            const size_t subMenuNamePadding = (maxWidth / 2) - (subMenuNameLen / 2);
            // add spaces before sub menu name
            ss << std::string(subMenuNamePadding, ' ');

            ss << " " <<  m_Name << '\n';

            // add border chars after sub menu name
            ss << std::string(maxWidth, DBG_MENU_BORDER) << '\n';

            // add 2 for space before and after the name
            const size_t subMenuDescriptionLen = m_Description.size() + 2;
            const size_t subMenuDescriptionPadding = (maxWidth / 2) - (subMenuDescriptionLen / 2);
            // add spaces before sub menu name
            ss << std::string(subMenuDescriptionPadding, ' ');

            ss << " " <<  m_Description << "\n\n";

            m_DisplayStr = ss.str();
        }

        void _AddMenuFooter(std::stringstream &ss, const uint16_t maxWidth) {
            ss << std::string(maxWidth, DBG_MENU_BORDER) << '\n';
            ss << std::string(maxWidth, DBG_MENU_BORDER) << '\n';
        }

    public:
        Menu(const std::string & name,
             const std::string & description,
             const std::vector<SubMenu> & subMenus) :
             PrintableEntity(name, description),
             m_SubMenus{subMenus}
             {
                m_Width = GetSubElementWithMaxWidth();
             }

        /**
         * Execute command
         * @param cmdName - the name of the command to execute (must be unique)
         * @return - true if found command to execute, false otherwise
         */
        bool ExecuteCommand(const std::string & cmdName) const {
            if (m_SubMenus.empty()) {
                return false;
            }
            for (const auto subMenu : m_SubMenus) {
                if (subMenu.ExecuteCommandIfExist(cmdName)) {
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

        void BuildDisplayString(const size_t maxWidth) override {

            std::stringstream ss;

            _AddMenuHeader(ss, maxWidth);

//            std::for_each(m_SubMenus.begin(), m_SubMenus.end(), [&](SubMenu& submenu){
//                submenu.BuildDisplayString(maxWidth);
//                ss << submenu; });


            _AddMenuFooter(ss, maxWidth);

            m_DisplayStr = ss.str() + '\n';
        }

    };

}

#endif //DEBUG_MENU_DBGMENU_H
