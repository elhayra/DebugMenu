
#ifndef DEBUG_MENU_DBGMENU_H
#define DEBUG_MENU_DBGMENU_H

#include "DbgSubMenu.h"
#include "DbgNamedEntity.h"
#include "DbgPrintSettings.h"



#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

namespace dbg {


    class Menu : public NamedEntity{
    private:
        const std::vector<SubMenu> m_SubMenus;

        std::string m_DisplayStr;

        void _BuildPrintStr() {

            // calculate maximum sub menu width
            uint16_t maxSubMenuWidth = 0;
            for (const auto & subMenu : m_SubMenus) {
                maxSubMenuWidth = std::max(maxSubMenuWidth, subMenu.GetWidth());
            }

            std::stringstream ss;

            _AddMenuHeader(ss, maxSubMenuWidth);

            std::for_each(m_SubMenus.begin(), m_SubMenus.end(),
                    [&ss](const SubMenu subMenu){ ss << subMenu; });

            _AddMenuFooter(ss, maxSubMenuWidth);

            m_DisplayStr = ss.str();
        }

        void _AddMenuHeader(std::stringstream &ss, const uint16_t maxSubMenuWidth) {

            // add title top border
            ss << std::string(maxSubMenuWidth, DBG_MENU_BORDER) << '\n';

            // add 2 for space before and after the name
            const size_t subMenuNameLen = m_Name.size() + 2;
            const size_t subMenuNamePadding = (maxSubMenuWidth / 2) - (subMenuNameLen / 2);
            // add spaces before sub menu name
            ss << std::string(subMenuNamePadding, ' ');

            ss << " " <<  m_Name << '\n';

            // add border chars after sub menu name
            ss << std::string(maxSubMenuWidth, DBG_MENU_BORDER) << '\n';

            // add 2 for space before and after the name
            const size_t subMenuDescriptionLen = m_Description.size() + 2;
            const size_t subMenuDescriptionPadding = (maxSubMenuWidth / 2) - (subMenuDescriptionLen / 2);
            // add spaces before sub menu name
            ss << std::string(subMenuDescriptionPadding, ' ');

            ss << " " <<  m_Description << "\n\n";

            m_DisplayStr = ss.str();
        }

        void _AddMenuFooter(std::stringstream &ss, const uint16_t maxSubMenuWidth) {
            ss << std::string(maxSubMenuWidth, DBG_MENU_BORDER) << '\n';
            ss << std::string(maxSubMenuWidth, DBG_MENU_BORDER) << '\n';
        }

    public:
        Menu(const std::string & name,
             const std::string & description,
             const std::vector<SubMenu> & subMenus) :
             NamedEntity(name, description),
             m_SubMenus{subMenus}
             {
                 if ( ! m_SubMenus.empty() ) {
                     _BuildPrintStr();
                     return;
                 }
                 m_DisplayStr = "=== EMPTY MENU: " + m_Name + " ===\n";
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

        friend std::ostream &operator<<(std::ostream & output, const Menu &);


    };

}

#endif //DEBUG_MENU_DBGMENU_H
