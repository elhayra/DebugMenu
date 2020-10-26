#include <iostream>

#include "DbgMainMenu.h"

#include "MyExampleDebugMenu.h"


/**
 * === Features ===
 * - add submenu name automatically
// all declarations are done in place - no need to declare in header file
// easy to use arguments parsing functions
// valid number of params is checked automatically
// automatic "pretty printer" including spacing, padding, headlines and extendable screen width
// automatically add sub-menu name as prefix to its command names
// automatically print success or failure command message after execution
// automatically show help in case of parameters error
// use '!' command prefix to execute command by number id as a shortcut
// use '@' command prefix to perform accurate time measurement of execution
 */

//--------TODO---------
/**
 * - add documentation to the debug main menu description about the ! and # prefixes
 * - all sub menues should be as long as the longest sub
 * menu (and the same for Menu), so drawing logic should be moved up to the *main* menu.
 * All drawing logic is similar, so move it to the MainMenu, and then all other components
 * should only return their width, but the MainMenu check what is the comp with max widht,
 * and will draw all accordingly
 *
 * - add printings for Command and test that it looks good with the description and params
 *
 * - if command fails because of wrong params, print help automatically
 *
 * - validate uniqueness of each submenu name
 *
 * - validate uniqueness of each command in submenu
 *
//todo: write macros to assert params boundaries and print auto error with numbers in case failed

//todo: if command/submenu/menu already exist, print error
//todo: automatically print command help menu if params are wrong or num of params is wrong
//todo: move includes and impl code  to the right place in cpp file
 *
//todo: check params bound by user definition
// todo; macros to create callback functions with description of the debug func and params boundaries
//todo: auto padding in printing
//todo: add option to add title to a group of commands
// todo : add option to press a number to execute command
//todo: add option to print verbose commands with the help lines
//todo: automatically count the number of params user defined and compare to params received input
//todo: apply bit error checking to all conversions
//todo: user colors for menus, commands, options, outputs
 //todo: add documentation comments wherever possible

// parser prints errors internally
// easier APIs to remember and use


//todo: print error in case string is empty in the macro
 *
 */
//--------BUGS----------
/**
 * - fix un-even len of "TuringMachine" submenu borders
 *
 * - fix "MyMenuWithNothing" submenu borders when it have no commands
 */

//--------TESTS---------
//todo: test empty menu (with no subMenus)
//todo: write tests for all params functions
//todo: write tests for getting params of bad strings line "sdf 98 1" or strings where length doesnt match the num of args in the string
//todo: write test for trying to get more args than exist
//todo: write test for duplicate command/menu
//todo: write test for non-exist command/menu
//todo: add colors to printings
//todo: print temp error with printf for all the errors todo: and test them
//todo: create only sub menus and menus with no commands in them, or very very short commands and very long menus names to see if menus padding is ruined

int main() {

//    std::string str = "0x31";
//    dbg::Args::Inst().SetArgs(str.c_str(), 1);
//
//    dbg::hex a = dbg::GetParam<dbg::hex>();
//
//
//    printf("param is %lld", a.Value);


    // register your debug menu to main menu
    dbg::MainMenu::Instance().AddMenu(MyExampleDebugMenu::LoadDebugMenu());

    dbg::MainMenu::Instance().Print();

    // I could count the params automatically, but we already get them from the current implementation
    dbg::MainMenu::Instance().ExecuteCommand("@PutinMenuLaunchRockets", "15 elhay", 2);

    dbg::MainMenu::Instance().PrintCommandHelp("PutinMenuLaunchRockets");

    return 0;
}



