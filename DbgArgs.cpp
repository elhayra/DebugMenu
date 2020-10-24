

#include "DbgArgs.h"
#include <cstring>

namespace dbg {


//    uint8_t Args::_CountParams() const {
//        uint16_t idx = 0;
//        bool seenSpace = true;
//        uint8_t numParams = 0;
//        while (idx < m_CharsArrSize) {
//           if (m_CharsArr[idx++] != ' ') {
//               if (seenSpace) {
//                   seenSpace = false;
//                   ++numParams;
//               }
//           } else {
//               seenSpace = true;
//           }
//        }
//        return numParams;
//    }

    void Args::SetArgs(const char * charsArr, const uint8_t numParams) {
        m_CharsArrSize = std::strlen(charsArr);
        m_CharsArr = charsArr;
        m_NumOfParams = numParams;
        m_CurrentParam = 0;
        m_CurrentIndex = 0;
    }

    std::string Args::GetNext() {
        //todo: turn pre-cond checks into RT_ASSERT
        if (m_CharsArr == nullptr) {
            printf("error: %s\n", __PRETTY_FUNCTION__);// todo: print error, we are out of bound. maybe the error should be more like a friendly warning to tell the user that he expected a param, but no param found

            return "";
        }
        if (m_CurrentParam >= m_NumOfParams) {
            printf("error: %s\n", __PRETTY_FUNCTION__);// todo: print error, we are out of bound. maybe the error should be more like a friendly warning to tell the user that he expected a param, but no param found
            return "";
        }
        if (m_CurrentIndex >= m_CharsArrSize) {
            printf("error: %s\n", __PRETTY_FUNCTION__);// todo: print error, we are out of bound. maybe the error should be more like a friendly warning to tell the user that he expected a param, but no param found
            return "";
        }

        // advance until find a non space character
        while ((m_CurrentIndex < m_CharsArrSize) && (m_CharsArr[m_CurrentIndex] == ' ')) {
            ++m_CurrentIndex;
        }

        // read characters until the next space is seen
        std::string paramStr;
        char ch;
        while (m_CurrentIndex < m_CharsArrSize) {
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