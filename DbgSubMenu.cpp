
#include "DbgSubMenu.h"

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

// min chars to put before and after
// the sub-menu name. This will also determine
// the min width along with the sub-menu name
#define MIN_PRE_POST_BORDER_NAME_CHARS   3

namespace dbg {

    SubMenu::SubMenu(const std::string & name,
                     const std::string & description,
                     const std::vector<Command> & cmds) :
            PrintableEntity(name, description),
            m_Commands{cmds}
    {
        // set min width as a starting point
        m_Width = m_Name.size() + (MIN_PRE_POST_BORDER_NAME_CHARS * 2);

        if ( ! m_Commands.empty() ) {
            _AddCommandsNamePrefix();
            _CalcColsMaxWidths();
        }
    }

    void SubMenu::_AddCommandsNamePrefix() {
        std::for_each(m_Commands.begin(), m_Commands.end(), [&](Command& cmd){
            cmd.AddSubMenuNameAsPrefix(Name()); });
    }

    void SubMenu::_CalcColsMaxWidths() {
        // calculate max width of each column
        for (int cmdIdx = 0; cmdIdx < m_Commands.size(); ++cmdIdx) {
            const auto & cmd = m_Commands.at(cmdIdx);
            const uint8_t cmdColIdx = cmdIdx % DBG_NUM_CMD_IN_ROW;
            m_ColsMaxWidth.at(cmdColIdx) = std::max(cmd.Width(), m_ColsMaxWidth.at(cmdColIdx));
        }

        size_t cmdLineMaxWidth = 0;
        // calculate screen width
        for (const auto colWidth : m_ColsMaxWidth) {
            cmdLineMaxWidth += colWidth; // add cols widths
        }
        // add cols spacers: we have N commands that are separated by N-1 spacers
        cmdLineMaxWidth += (DBG_NUM_CMD_SPACE_CHRS * (DBG_NUM_CMD_IN_ROW-1));

        m_Width = std::max(m_Width, cmdLineMaxWidth);
    }

    void SubMenu::Print(const size_t maxWidth) const {

        std::cout << std::endl;

        _PrintSubMenuHeader(maxWidth);

        // print the commands by columns
        for (int cmdIdx = 0; cmdIdx < m_Commands.size(); ++cmdIdx) {
            const auto & cmd = m_Commands.at(cmdIdx);
            const uint8_t cmdColIdx = cmdIdx % DBG_NUM_CMD_IN_ROW;
            const int spaces = m_ColsMaxWidth.at(cmdColIdx) - cmd.Width();
            if (spaces < 0) {
                printf("ERROR: %s\n", __PRETTY_FUNCTION__); // spaces can't be negative
                return;
            }
            cmd.Print();
            std::cout << std::string(spaces + DBG_NUM_CMD_SPACE_CHRS, ' ');
            if (cmdColIdx == DBG_NUM_CMD_IN_ROW-1) {
                std::cout << std::endl;
            }
        }
        std::cout << std::endl;

        _PrintSubMenuFooter(maxWidth);

        std::cout << std::endl;
    }

    void SubMenu::_PrintSubMenuHeader(const size_t maxWidth) const {
        // add 2 for space before and after the name
        const std::string paddedName = ' ' + m_Name + ' ';

        int preNameBorder = (maxWidth / 2) - (paddedName.size() / 2);
        if (preNameBorder < 0) {
            printf("ERROR: %s\n", __PRETTY_FUNCTION__); // spaces can't be negative
            return;
        }

        // add border chars before sub menu name
        std::cout << std::string(preNameBorder, DBG_SUB_MENU_BORDER_CHAR);
        std::cout << " " <<  m_Name << " ";

        int postNameBorder = maxWidth - paddedName.size() - preNameBorder;
        if (postNameBorder > 0) {
            std::cout << std::string(postNameBorder, DBG_SUB_MENU_BORDER_CHAR) << '\n';
        }
    }

    void SubMenu::_PrintSubMenuFooter(const size_t maxWidth) const {
        std::cout << std::string(maxWidth, DBG_SUB_MENU_BORDER_CHAR) << '\n';
    }


    bool SubMenu::ExecuteCommandIfExist(const std::string & cmdName) const {

        if (m_Commands.empty()) {
            return false;
        }

        // by default find by name
        std::function<bool(const Command&)> comparatorFunc = [cmdName](const Command& cmd) {
            return cmd.Name() == cmdName;
        };
        if (cmdName.rfind('!') == 0) {
            std::string cmdNameCopy = cmdName;
            cmdNameCopy.erase(0, 1); // remove first char ('!') so only id is left
            uint16_t inputCmdId = 0;
            try {
                inputCmdId = std::stoi(cmdNameCopy);// convert string id to number
            } catch (std::invalid_argument) {
                printf("error: %s\n", __PRETTY_FUNCTION__);//todo: print error - conversion to int failed
                return false;
            }
            // if starts with '!' find by id
            comparatorFunc = [&inputCmdId](const Command& cmd) {
                return cmd.Id() == inputCmdId;
            };
        }

        const auto cmdItr = std::find_if(m_Commands.begin(), m_Commands.end(), comparatorFunc);

        if (cmdItr != std::end(m_Commands)) {
            (*cmdItr)(); // execute command callback
            return true;
        }
        return false;
    }

}