

#ifndef DEBUG_MENU_DBGPRINTABLEENTITY_H
#define DEBUG_MENU_DBGPRINTABLEENTITY_H

#include <string>

namespace dbg {

    class PrintableEntity {
    protected:
        std::string m_Name;
        const std::string m_Description;
        size_t m_Width {0};
        std::string m_DisplayStr;

        PrintableEntity(const std::string & name,
              const std::string & description) :
              m_Name{name},
              m_Description{description} {  }


    public:
        virtual ~PrintableEntity() = default;

        /**
         * Build display string
         */
        virtual void BuildDisplayString(const size_t maxWidth) = 0;

        /**
         * @return sub-element with maximum width
         */
        virtual size_t GetSubElementWithMaxWidth() const { return 0; }

        std::string Name() const { return m_Name; }

        std::string Display() const { return m_DisplayStr; }

        std::string Description() const { return m_Description; }

        size_t Width() const {
            if (m_Width == 0) { // not initialized
                printf("error: %s\n", __PRETTY_FUNCTION__);
            }
            return m_Width;
        }
    };

    std::ostream &operator<<(std::ostream & output, const dbg::PrintableEntity& cmd);

}

#endif //DEBUG_MENU_DBGPRINTABLEENTITY_H
