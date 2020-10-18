

#ifndef DEBUG_MENU_DBGSUBMENU_H
#define DEBUG_MENU_DBGSUBMENU_H


#include "DbgCommand.h"
#include "DbgNamedEntity.h"
#include "DbgPrintSettings.h"


#include <string>
#include <vector>





#include <iostream>
#include <array>
#include <algorithm>

//todo: if command is bigger than one line width, print error.
//todo: if command already exist, print error
//todo: move all impl code to cpp
//todo: automatically print command help menu if params are wrong or num of params is wrong
//todo: move includes and impl code  to the right place in cpp file


namespace dbg {


    class SubMenu : public NamedEntity{
    private:

        const std::vector<Command> m_Commands;
        std::string m_DisplayStr;
        uint16_t m_Width {0};

        void _BuildPrintStr() {

            std::stringstream ss;


           std::vector<std::array<const Command*, DBG_NUM_CMD_IN_ROW>> m_CmdMatrix;

           m_CmdMatrix.push_back({nullptr}); // insert first row

            uint8_t lineIdx = 0;
            uint8_t numCharsInCurrentLine = 0;
            uint8_t cmdIdx = 0;
            int availableChars = 0;
            bool insertCmdToCurrLine = false;

            // array to hold max command length in each column
            std::array<size_t, DBG_NUM_CMD_IN_ROW> colsMaxWidth{0};

            auto startNewLine = [&]() {
                m_CmdMatrix.push_back({nullptr});
                ++lineIdx;
                numCharsInCurrentLine = 0;
            };

            do {
                const auto &cmd = m_Commands.at(cmdIdx);

                const uint8_t cmdColIdx = cmdIdx % DBG_NUM_CMD_IN_ROW;

                if (cmdColIdx < DBG_NUM_CMD_IN_ROW) { // don't exceed num of allowed cmds in a row
                    m_CmdMatrix.at(lineIdx).at(cmdColIdx) = &cmd; // add cmd to current line
                    // find max command length in each column, later
                    // will be used to determine column spaces
                    const size_t cmdCharsLen = cmd.GetPrintedNameLen();
                    colsMaxWidth.at(cmdColIdx) = std::max(cmdCharsLen, colsMaxWidth.at(cmdColIdx));
                    numCharsInCurrentLine += cmdCharsLen;

                    ++cmdIdx;

                    if (cmdIdx == (lineIdx * DBG_NUM_CMD_IN_ROW + DBG_NUM_CMD_IN_ROW)) {
                        startNewLine();
                    }

                } else { // no space in current line, open a new one
                    startNewLine();
                }

            } while (cmdIdx < m_Commands.size());

            // calculate screen width
            for (const auto colWidth : colsMaxWidth) {
               m_Width += colWidth;
            }

            // we have N commands that are separated by N-1 spacers
            m_Width += (DBG_NUM_CMD_SPACE_CHRS * (DBG_NUM_CMD_IN_ROW-1));

            _AddSubMenuHeader(ss);

            for (const auto & line : m_CmdMatrix) {
                for (uint8_t cmdIdx = 0; cmdIdx < DBG_NUM_CMD_IN_ROW; ++cmdIdx) {
                    if (line.at(cmdIdx) != nullptr) {
                        const Command & cmd = *(line.at(cmdIdx));
                        const uint8_t spaces = colsMaxWidth.at(cmdIdx) - cmd.GetPrintedNameLen();
                        ss << cmd << std::string(spaces + DBG_NUM_CMD_SPACE_CHRS, ' ');
                    }
                }
                ss << '\n';
            }

            _AddSubMenuFooter(ss);

            m_DisplayStr = ss.str();
        }

        void _AddSubMenuHeader(std::stringstream & ss) {
            // add 2 for space before and after the name
            const size_t subMenuNameLen = m_Name.size() + 2;
            const size_t subMenuNamePadding = (m_Width / 2) - (subMenuNameLen / 2);
            // add border chars before sub menu name
            ss << std::string(subMenuNamePadding, DBG_SUB_MENU_BORDER_CHAR);

            ss << " " <<  m_Name << " ";

            // add border chars after sub menu name
            ss << std::string(subMenuNamePadding, DBG_SUB_MENU_BORDER_CHAR) << '\n';

        }

        void _AddSubMenuFooter(std::stringstream & ss) {
            ss << std::string(m_Width, DBG_SUB_MENU_BORDER_CHAR) << '\n';
        }

    public:
        SubMenu(const std::string & name,
             const std::string & description,
             const std::vector<Command> & cmds) :
                NamedEntity(name, description),
                m_Commands{cmds}
        {
            if ( ! m_Commands.empty() ) {
                _BuildPrintStr();
                return;
            }
            m_DisplayStr = "=== EMPTY SUB-MENU: " + m_Name + " ===\n";
        }

        /**
         * Execute command if it exist in this sub menu
         * @param cmdName - command name to execute
         * @return true if command name found in this sub menu, false otherwise
         */
        bool ExecuteCommandIfExist(const std::string & cmdName) const {

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
                    //todo: print error - conversion to int failed
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

        uint16_t GetWidth() const { return m_Width; }

        friend std::ostream &operator<<(std::ostream & output, const dbg::SubMenu& subMenu);
    };

}









#endif //DEBUG_MENU_DBGSUBMENU_H
