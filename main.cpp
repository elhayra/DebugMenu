#include <iostream>

#include "DbgMainMenu.h"

#include "MyExampleDebugMenu.h"

//todo: write tests for all params functions
//todo: write tests for getting params of bad strings line "sdf 98 1" or strings where length doesnt match the num of args in the string
//todo: write test for trying to get more args than exist
//todo: add colors to printings


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


    dbg::MainMenu::Instance().ExecuteCommand("!0", "15 elhay  s", 3);


    return 0;
}



