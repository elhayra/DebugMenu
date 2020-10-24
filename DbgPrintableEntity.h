

#ifndef DEBUG_MENU_DBGPRINTABLEENTITY_H
#define DEBUG_MENU_DBGPRINTABLEENTITY_H

#include <string>

namespace dbg {

    class PrintableEntity {
    protected:
        std::string m_Name;
        const std::string m_Description;
        size_t m_Width {0};

        PrintableEntity(const std::string & name,
              const std::string & description) :
              m_Name{name},
              m_Description{description} {  }


    public:
        virtual ~PrintableEntity() = default;

        /**
         * Build display string
         */
        virtual void Print(const size_t maxWidth) const = 0;

        /**
         * @return sub-element with maximum width
         */
        virtual size_t GetSubElementWithMaxWidth() const { return 0; }

        std::string Name() const { return m_Name; }

        std::string Description() const { return m_Description; }

        size_t Width() const {
            if (m_Width == 0) { // not initialized
                printf("error: %s\n", __PRETTY_FUNCTION__);
            }
            return m_Width;
        }
    };
}

#endif //DEBUG_MENU_DBGPRINTABLEENTITY_H
