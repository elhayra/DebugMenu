

#include "DbgArgs.h"


namespace dbg {

    void Args::SetArgs(const char * charsArr, uint8_t numOfParams) {
        m_CharsArr = charsArr;
        m_NumOfParams = numOfParams;
        m_CurrentParam = 0;
        m_CurrentIndex = 0;
    }

    std::string Args::GetNext() {
        if (m_CharsArr == nullptr || m_CurrentParam >= m_NumOfParams) {
            // todo: print error, we are out of bound. maybe the error should be more like a friendly warning to tell the user that he expected a param, but no param found
            return "";
        }

        // advance until find a non space character
        while (m_CharsArr[m_CurrentIndex] == ' ') {
            ++m_CurrentIndex;
        }

        // read characters until the next space is seen
        std::string paramStr;
        char ch;
        while (true) {
            ch = m_CharsArr[m_CurrentIndex++];
            if ((ch != ' ') && (ch != '\0')) {
                paramStr += ch;
            } else {
                break;
            }
        };

        ++m_CurrentParam;

        return paramStr;
    }

}