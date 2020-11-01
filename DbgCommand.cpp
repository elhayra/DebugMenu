

#include "DbgCommand.h"

namespace dbg {

    uint16_t Command::m_IdGen {0};


    Command::Command(const std::string &name,
            const std::string &description,
            const std::vector<Param> &params,
            const std::function<cmd_ret_t()> &callback) :
            PrintableEntity{name, description},
            m_Id{m_IdGen++},
            m_Params{params},
            m_Callback{callback}
    {
        _VerifyName();
        m_Width = m_Name.size();
    }

    Command::Command(const cmd_data_t & cmdData)  :
            PrintableEntity{cmdData.Name, cmdData.Description},
            m_Id{m_IdGen++},
            m_Params{cmdData.Params},
            m_Callback{cmdData.Callback}
    {
        _VerifyName();
        m_Width = m_Name.size();
    }

    Command::Command(const Command& other) :
            PrintableEntity{other.m_Name, other.m_Description},
            m_Id{other.m_Id},
            m_Params{other.m_Params},
            m_Callback{other.m_Callback}
    {
        _VerifyName();
        m_Width = other.Width();
    }

    void Command::_VerifyName() {
        if (m_Name.empty()) {
            printf("error name of command id: %d can't be blank %s\n", m_Id, __PRETTY_FUNCTION__); //todo: rt_err
        }
    }

    void Command::AddSubMenuNameAsPrefix(const std::string & subMenuName) {
        m_Name = subMenuName + m_Name;
        _UpdateWidthByName();
    }

    void Command::Print(const size_t maxWidth) const {
        std::cout << '[' + std::to_string(Id()) + "]-" + Name();
    }

    void Command::PrintHelp() const {
        std::cout << '\n' << Name() << ":\n"
                  << Description() << "\n\n";
        if (!m_Params.empty()) {
            std::for_each(m_Params.begin(), m_Params.end(),
                          [](const Param& param){ param.Print(); });
        }
    }

    bool Command::Run(const bool multiMeasure) const {
        if ( ! m_Callback ) {
            printf("error: %s\n", __PRETTY_FUNCTION__);//todo: print error, callback wasn't assigned
            return false;
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

} // end of dbg




