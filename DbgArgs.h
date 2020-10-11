

#ifndef DEBUG_MENU_DBGARGS_H
#define DEBUG_MENU_DBGARGS_H

#include <cstdint>
#include <string>

namespace dbg {

    class Args {
    private:
        const char * m_CharsArr {nullptr};
        uint8_t m_NumOfParams {0};
        uint8_t m_CurrentParam {0};
        uint16_t m_CurrentIndex {0};

        Args() = default;
        ~Args() = default;

    public:
        Args(const Args &) = delete;
        Args(const Args &&) = delete;
        Args & operator=(const Args &) = delete;
        Args & operator=(const Args &&) = delete;


        static Args & Inst() {
            static Args args;
            return args;
        }

        void SetArgs(const char * charsArr, uint8_t numOfParams);

        std::string GetNext();

    };


}



#endif //DEBUG_MENU_DBGARGS_H

