

#ifndef DEBUG_MENU_DBGCOMMAND_H
#define DEBUG_MENU_DBGCOMMAND_H

#include "DbgParam.h"

#include <string>
#include <vector>
#include <functional>
#include <iostream>
#include <sstream>
#include <chrono>

#include "DbgArgs.h"
#include "DbgPrintableEntity.h"


namespace dbg {

    struct cmd_ret_t {
        bool Success;
        std::string Message;
        cmd_ret_t(const bool success, const std::string& msg="") :
            Success{success}, Message{msg} { }
    };

    class Command : public PrintableEntity {
    private:
        static uint16_t m_IdGen;
        const uint16_t m_Id;
        std::function<cmd_ret_t()> m_Callback;
        const std::vector<Param> m_Params;

        void _UpdateWidthByName() { m_Width = m_Name.size() + 4; }

    public:
        Command(const std::string &name,
                const std::string &description,
                const std::vector<Param> &params,
                const std::function<cmd_ret_t()> &callback) :
                PrintableEntity{name, description},
                m_Id{m_IdGen++},
                m_Params{params},
                m_Callback{callback}
        {
            m_Width = m_Name.size();
        }

        Command(const Command& other) :
                PrintableEntity{other.m_Name, other.m_Description},
                m_Id{other.m_Id},
                m_Params{other.m_Params},
                m_Callback{other.m_Callback}
        {
            m_Width = other.Width();
        }

        Command(const Command&& other) = delete;

        uint16_t Id() const { return m_Id; }

        size_t NumOfParams() const { return m_Params.size(); }

        void AddSubMenuNameAsPrefix(const std::string & subMenuName) {
            m_Name = subMenuName + m_Name;
            _UpdateWidthByName();
        }

        void Print(const size_t maxWidth = 0) const override {
            std::cout << '[' + std::to_string(Id()) + "]-" + Name();
        }

        void PrintHelp() const {
            std::cout << '\n' << Name() << ":\n"
                      << Description() << "\n\n";
            if (!m_Params.empty()) {
                std::for_each(m_Params.begin(), m_Params.end(),
                        [](const Param& param){ param.Print(); });
            }
        }

        bool Run(const bool multiMeasure) const {
            if ( ! m_Callback ) {
                return false;
                printf("error: %s\n", __PRETTY_FUNCTION__);//todo: print error, callback wasn't assigned
            }

            uint16_t numOfMeasureIters = 1;
            if (multiMeasure) {
                numOfMeasureIters = 20000;
            }

            std::vector<uint64_t> durations;
            durations.reserve(numOfMeasureIters);
            cmd_ret_t summaryCmdRet{false};

            uint16_t itersLeftToRun = numOfMeasureIters;
            while (itersLeftToRun > 0) {
                const auto begin = std::chrono::steady_clock::now();

                auto cmdRet = m_Callback();
                summaryCmdRet.Success |= cmdRet.Success;
                summaryCmdRet.Message = cmdRet.Message;

                const auto end = std::chrono::steady_clock::now();

                const uint64_t duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();
                durations.push_back(duration);
                --itersLeftToRun;
            }

            uint64_t totalDurationNano = 0;
            for (const uint64_t duration : durations) {
                totalDurationNano += duration;
            }

            const uint64_t avgTimeNano = totalDurationNano / durations.size();

            if (summaryCmdRet.Success) {
                printf("\ncommand %s executed successfully\n", m_Name.c_str()); //todo: rt_info
            } else {
                printf("\ncommand %s failed\n", m_Name.c_str()); //todo: rt_info
                if ( ! summaryCmdRet.Message.empty() ) {
                   printf("command error: %s\n", summaryCmdRet.Message.c_str()); //todo: rt_info
                }
            }
            printf("ran %d iterations, avg execution time: %llu (nano)\n", numOfMeasureIters, avgTimeNano);

            return summaryCmdRet.Success;
        }


    };


}



#endif //DEBUG_MENU_DBGCOMMAND_H


