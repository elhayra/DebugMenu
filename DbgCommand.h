

#ifndef DEBUG_MENU_DBGCOMMAND_H
#define DEBUG_MENU_DBGCOMMAND_H

#include "DbgParam.h"

#include <string>
#include <vector>
#include <functional>
#include <iostream>
#include <sstream>

namespace dbg {
    class Command {
    private:
        static uint16_t m_IdGen;
        const uint16_t m_Id;
        const std::string m_Name;
        const std::string m_Description;
        std::function<void()> m_Callback;
        const std::vector<Param> m_Params;

        size_t m_PrintedNameLen{0};

        /**
         * calculate full name (name + id) characters length
         */
        void _CalculatePrintedNameLen() {
            uint16_t id = m_Id;
            // find num of digits in id
            uint8_t idLen = 0;
            do {
                ++idLen;
                id = id % 10;
                id = id / 10;
            } while (id != 0);

            // the format is "[id]-name"
            // add 3 chars:
            // 2 - for the "[" before and after "]" the id,
            // 1 - for the space after the "]"
            m_PrintedNameLen = m_PrintedNameLen = idLen + m_Name.size() + 3;
        }

    public:
        Command(const std::string &name,
                const std::string &description,
                const std::vector<Param> &params,
                const std::function<void()> &callback) :
                m_Id{m_IdGen++},
                m_Name{name},
                m_Description{description},
                m_Params{params},
                m_Callback{callback}
                {
                    _CalculatePrintedNameLen();
                }

        Command(const Command& other) :
                m_Id{other.m_Id},
                m_Name{other.m_Name},
                m_Description{other.m_Description},
                m_Params{other.m_Params},
                m_Callback{other.m_Callback},
                m_PrintedNameLen{other.m_PrintedNameLen}
        {
        }

        Command(const Command&& other) :
            m_Id{other.m_Id},
            m_Name{std::move(other.m_Name)},
            m_Description{std::move(other.m_Description)},
            m_Params(std::move(other.m_Params)),
            m_Callback{std::move(other.m_Callback)},
            m_PrintedNameLen{other.m_PrintedNameLen}
        {
        }


        size_t GetPrintedNameLen() const { return m_PrintedNameLen; }
        uint16_t Id() const { return m_Id; }
        std::string Name() const { return m_Name; }

        void operator()() const {
            if (m_Callback) {
                m_Callback();
            } else {
               //print error, callback wasn't assigned
            }
        }


    };

    std::ostream &operator<<(std::ostream & output, const dbg::Command& cmd);

}



#endif //DEBUG_MENU_DBGCOMMAND_H


