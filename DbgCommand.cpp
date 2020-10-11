

#include "DbgCommand.h"

namespace dbg {

    uint16_t Command::m_IdGen {0};


    std::ostream &operator<<(std::ostream & output, const dbg::Command& cmd) {
        output << "[" << static_cast<int>(cmd.Id()) << "]-" << cmd.Name();
        return output;
    }
}




