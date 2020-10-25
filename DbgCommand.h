

#ifndef DEBUG_MENU_DBGCOMMAND_H
#define DEBUG_MENU_DBGCOMMAND_H

#include "DbgParam.h"

#include <string>
#include <vector>
#include <functional>
#include <iostream>
#include <sstream>
#include "DbgArgs.h"
#include "DbgPrintableEntity.h"


namespace dbg {
    class Command : public PrintableEntity {
    private:
        static uint16_t m_IdGen;
        const uint16_t m_Id;
        std::function<bool()> m_Callback;
        const std::vector<Param> m_Params;

        void _UpdateWidthByName() { m_Width = m_Name.size() + 4; }

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

        uint16_t Id() const { return m_Id; }

        void AddSubMenuNameAsPrefix(const std::string & subMenuName) {
            m_Name = subMenuName + m_Name;
            _UpdateWidthByName();
        }

        void Print(const size_t maxWidth = 0) const override {
            std::cout << '[' + std::to_string(Id()) + "]-" + Name();
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


}



#endif //DEBUG_MENU_DBGCOMMAND_H


