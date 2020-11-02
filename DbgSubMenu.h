

#ifndef DEBUG_MENU_DBGSUBMENU_H
#define DEBUG_MENU_DBGSUBMENU_H


#include "DbgCommand.h"
#include "DbgPrintableEntity.h"
#include "DbgPrintSettings.h"


#include <array>



namespace dbg {


    struct submenu_data_t {
        std::string Name;
        std::string Description;
        std::vector<Command> Commands;
    };

    class SubMenu : public PrintableEntity{
    private:

        std::vector<Command> m_Commands;

        // hold max command length in each column
        std::array<size_t, DBG_NUM_CMD_IN_ROW> m_ColsMaxWidth {{0}};

        void _PrintSubMenuHeader(const size_t maxWidth) const ;

        void _PrintSubMenuFooter(const size_t maxWidth) const ;

        void _CalcColsMaxWidths();

        void _AddCommandsNamePrefix(const std::string& name);

        /**
         * Execute command, return true if succeeded
         * @param cmd
         * @param numParams
         * @param multiMeasure
         * @return
         */
        bool _ExecuteCommand(const Command& cmd,
                const uint8_t numParams,
                const bool multiMeasure) const ;

        /**
         * Set min width as starting poing
         */
        void _SetMinWidth();

    public:

        SubMenu(const std::string & name,
             const std::string & description,
             const std::vector<Command> & cmds);

        SubMenu(const submenu_data_t& submenuData);

        void MenuHolderInit(const std::string& holderName);


        /**
         * Execute command if it exist in this sub menu (search by name)
         * @param cmdName - command name to execute
         * @return true if the command was found
         */
        bool ExecuteCommandByName(const std::string &cmdName,
                const uint8_t numParams,
                const bool multiMeasure = false) const ;

        /**
         * Execute command if it exist in this sub menu (search by id)
         * @param cmdName - command name to execute
         * @return true if the command was found
         */
        bool ExecuteCommandById(const uint16_t id, const uint8_t numParams) const;

        /**
         * Print all commands that contains a given name
         * @param name
         */
        void PrintCommandsContainingName(const std::string& name) const;

        /**
         * print command help if it exist in this sub menu
         * @param cmdName - command name
         * @return true if command found, false otherwise
         */
        bool PrintCommandHelpIfExist(const std::string & cmdName) const ;

        void Print(const size_t maxWidth) const override;

    };

}









#endif //DEBUG_MENU_DBGSUBMENU_H
