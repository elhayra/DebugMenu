#include <iostream>

#include "DbgMainMenu.h"

#include "MyExampleDebugMenu.h"

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


    dbg::MainMenu::Instance().ExecuteCommand("!0", "15 elhay");//todo: remove num params, count myself


    return 0;
}



