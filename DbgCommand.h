

#ifndef DEBUG_MENU_DBGCOMMAND_H
#define DEBUG_MENU_DBGCOMMAND_H

#include "DbgParam.h"

#include <string>
#include <vector>
#include <functional>
#include <iostream>
#include <sstream>
#include "DbgArgs.h"
#include "DbgNamedEntity.h"


namespace dbg {
    class Command : public PrintableEntity {
    private:
        static uint16_t m_IdGen;
        const uint16_t m_Id;
        std::function<bool()> m_Callback;
        const std::vector<Param> m_Params;

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
            m_Width = idLen + m_Name.size() + 3;
        }

    public:
        Command(const std::string &name,
                const std::string &description,
                const std::vector<Param> &params,
                const std::function<bool()> &callback) :
                PrintableEntity{name, description},
                m_Id{m_IdGen++},
                m_Params{params},
                m_Callback{callback}
        {
        }

        Command(const Command& other) :
                PrintableEntity{other.m_Name, other.m_Description},
                m_Id{other.m_Id},
                m_Params{other.m_Params},
                m_Callback{other.m_Callback}
        {
        }

        Command(const Command&& other) :
            PrintableEntity{std::move(other.m_Name), std::move(other.m_Description)},
            m_Id{other.m_Id},
            m_Params(std::move(other.m_Params)),
            m_Callback{std::move(other.m_Callback)}
        {
        }

        size_t GetPrintedNameLen() const {
            if (m_Width == 0) { // not initialized
                printf("error: %s\n", __PRETTY_FUNCTION__);//todo: print error
            }
            return m_Width;
        }

        uint16_t Id() const { return m_Id; }

        void AddSubMenuNameAsPrefix(const std::string & subMenuName) {
            m_Name = subMenuName + m_Name;
            _CalculatePrintedNameLen();
        }

        bool operator()() const {
            auto a = Args::Inst().GetNumOfParams();
            auto b = m_Params.size();
            if (Args::Inst().GetNumOfParams() != m_Params.size()) {
                printf("error: %s\n", __PRETTY_FUNCTION__);//todo: print error
                return false;
            }
            if (m_Callback) {
                return m_Callback();
            }
            printf("error: %s\n", __PRETTY_FUNCTION__);//todo: print error, callback wasn't assigned
           return false;
        }

        bool operator==(const Command& other) const {
            return ((&other == this) ||
                    (other.Name() == this->Name()) ||
                    (other.Id() == this->Id()));
        }
    };

    std::ostream &operator<<(std::ostream & output, const dbg::Command& cmd);

}



#endif //DEBUG_MENU_DBGCOMMAND_H


