
#include "DbgSubMenu.h"

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>


namespace dbg {

    SubMenu::SubMenu(const std::string & name,
                     const std::string & description,
                     const std::vector<Command> & cmds) :
            PrintableEntity(name, description),
            m_Commands{cmds}
    {
        if ( ! m_Commands.empty() ) {
            for (auto &cmd : m_Commands) {
                cmd.Print();
            }

            _FillCmdMatrix();
        }
    }


    void SubMenu::_FillCmdMatrix() {
        m_CmdMatrix.push_back({nullptr}); // insert first row

        uint8_t lineIdx = 0;
        uint8_t cmdIdx = 0;



        auto startNewLine = [&]() {
            m_CmdMatrix.push_back({nullptr});
            ++lineIdx;
        };

        while (cmdIdx < m_Commands.size()) {
            const auto &cmd = m_Commands.at(cmdIdx);

            const uint8_t cmdColIdx = cmdIdx % DBG_NUM_CMD_IN_ROW;

            if (cmdColIdx < DBG_NUM_CMD_IN_ROW) { // don't exceed num of allowed cmds in a row
                m_CmdMatrix.at(lineIdx).at(cmdColIdx) = &cmd; // add cmd to current line
                // find max command length in each column, later
                // will be used to determine column spaces
                const size_t cmdCharsLen = cmd.Width();
                m_ColsMaxWidth.at(cmdColIdx) = std::max(cmdCharsLen, m_ColsMaxWidth.at(cmdColIdx));

                ++cmdIdx;

                if (cmdIdx == (lineIdx * DBG_NUM_CMD_IN_ROW + DBG_NUM_CMD_IN_ROW)) {
                    startNewLine();
                }

            } else { // no space in current line, open a new one
                startNewLine();
            }
        }

        // calculate screen width
        for (const auto colWidth : m_ColsMaxWidth) {
            m_Width += colWidth; // add cols widths
        }
        // add cols spacers: we have N commands that are separated by N-1 spacers
        m_Width += (DBG_NUM_CMD_SPACE_CHRS * (DBG_NUM_CMD_IN_ROW-1));
    }

    void SubMenu::Print(const size_t maxWidth) const {

        std::cout << std::endl;

        _PrintSubMenuHeader(maxWidth);

        for (const auto & line : m_CmdMatrix) {
            for (uint8_t cmdIdx = 0; cmdIdx < DBG_NUM_CMD_IN_ROW; ++cmdIdx) {
                if (line.at(cmdIdx) != nullptr) {
                    const Command & cmd = *(line.at(cmdIdx));
                    const uint8_t spaces = m_ColsMaxWidth.at(cmdIdx) - cmd.Width();
                    cmd.Print();
                    std::cout << std::string(spaces + DBG_NUM_CMD_SPACE_CHRS, ' ');
                }
            }
            std::cout << std::endl;
        }

        _PrintSubMenuFooter(maxWidth);

        std::cout << std::endl;
    }

    void SubMenu::_PrintSubMenuHeader(const size_t maxWidth) const {
        // add 2 for space before and after the name
        const size_t subMenuNameLen = m_Name.size() + 2;

        size_t subMenuNamePadding = 0;
        if (maxWidth >= subMenuNameLen) {
            subMenuNamePadding = (maxWidth / 2) - (subMenuNameLen / 2);
        }
        // add border chars before sub menu name
        std::cout << std::string(subMenuNamePadding, DBG_SUB_MENU_BORDER_CHAR);

        std::cout << " " <<  m_Name << " ";

        // add border chars after sub menu name
        std::cout << std::string(subMenuNamePadding, DBG_SUB_MENU_BORDER_CHAR) << '\n';

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