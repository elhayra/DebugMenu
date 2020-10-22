#include <iostream>

#include "DbgMainMenu.h"

#include "MyExampleDebugMenu.h"


/**
 * Features
 * - add submenu name automatically
 * - validate uniqueness of each submenu name
 * - validate uniqueness of each command in submenu
 */

//--------TODO---------
/**
 * - add error printings to all places with "todo"
 *
 * - all sub menues should be as long as the longest sub
 * menu (and the same for Menu), so drawing logic should be moved up to the *main* menu.
 * All drawing logic is similar, so move it to the MainMenu, and then all other components
 * should only return their width, but the MainMenu check what is the comp with max widht,
 * and will draw all accordingly
 *
 * - bring "todo" from all other files to this spot
 *
 * - bring "features" from all other files to this spot
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

    // I could count the params automatically, but we already get them from the current implementation
    dbg::MainMenu::Instance().ExecuteCommand("!0", "15 elhay", 2);


    return 0;
}



