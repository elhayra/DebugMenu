#include <iostream>

#include "DbgMainMenu.h"

#include "MyExampleDebugMenu.h"
#include "MyExampleDbgMenu2.h"



// === Features ===
// add submenu name automatically to commands
// all declarations are done in place - no need to declare in header file
// easy to use arguments parsing functions, no need to remember complicated functions names, all done with same GetParam() function
// valid number of params is checked automatically
// automatic "pretty printer" including spacing, padding, headlines and extendable screen width
// automatically add sub-menu name as prefix to its command names
// automatically print success or failure command message after execution
// automatically show help in case of parameters error
// use '!' command prefix to execute command by number id as a shortcut
// use '@' command prefix to perform accurate time measurement of execution
// use '#' command prefix to search command that contains name X
// after command execution success / failure message will be printed automatically with appropriate error if available
// return boolean or dbg::cmd_ret_t{bool, string} type from function in case you want to print error message
// in case command failed because of wrong number of params, print help text automatically to help user
// params parser detect '0x' prefix automatically and parse the number as hex
// if command/submenu/menu already exist, print error
// 2 ways to declare commands/menus



//--------TODO---------


//--------BUGS----------


//--------TESTS---------
//todo: test empty menu (with no subMenus) -- V
//todo: write tests for all params functions
//todo: write tests for getting params of bad strings line "sdf 98 1" or strings where length doesnt match the num of args in the string
//todo: write test for trying to get more args than exist
//todo: write test for duplicate command/menu -- V
//todo: write test for non-exist command/menu -- V
//todo: create only sub menus and menus with no commands in them, or very very short commands and very long menus names to see if menus padding is ruined


int main() {


    // register your debug menu to main menu
    dbg::MainMenu::Instance().AddMenu(MyExampleDebugMenu::LoadDebugMenu());
    dbg::MainMenu::Instance().AddMenu(MyExampleDebugMenu2::LoadDebugMenu()); //second menu

    dbg::MainMenu::Instance().Print();

    // I could count the params automatically, but we already get them from the current implementation
//    dbg::MainMenu::Instance().ExecuteCommand("Finisar400ZrLaunchRockets", "15 elhay", 2); // run by name
//    dbg::MainMenu::Instance().ExecuteCommand("!0", "15 elhay", 2); // run by id
//    dbg::MainMenu::Instance().ExecuteCommand("#zevik", "", 0); // search cmds with sub string
//    dbg::MainMenu::Instance().ExecuteCommand("@Finisar400ZrMySuperZevikCommand", "", 0); // benchmark cmd

//    dbg::MainMenu::Instance().PrintCommandHelp("MyOtherMenuBuy6Submarines");

    return 0;
}



