//
// Created by Eli Eli on 2020-11-01.
//

#include "MyExampleDbgMenu2.h"


#include "DbgMenu.h"
#include "DbgParamsParser.h"


#include <iostream>





dbg::Menu MyExampleDebugMenu2::LoadDebugMenu() {




    ////////////////////////////////////////
    //           COMMANDS
    ////////////////////////////////////////

    // define commands
    dbg::Command cmd1{{
        .Name = "Buy6Submarines",
        .Description = "command 1 description",
        .Params = {
                dbg::param_data_t{
                    .Name = "My param",
                    .Description = "My param description",
                    .Options = {
                            {"opt1 value", "opt1 name", "opt1 description"},
                            {"opt2 value", "opt2 name"} // value description is optional
                    }
                },
                dbg::param_data_t{
                        .Name = "My param 2",
                        .Description = "My param description 2",
                        .Options = {
                                {"opt1 value", "opt1 name", "opt1 description"},
                                {"opt2 value", "opt2 name"} // value description is optional
                        }
                },
        },
        .Callback = []() { //callback
            std::cout << "we have " << (int)dbg::GetNumOfParams() << " params available" << std::endl;

            //no need to check the num of params, this is done automatically.
            uint8_t myParam1 = dbg::GetParam<uint8_t>(); // get uint8_t param
            std::string myName = dbg::GetParam<std::string>();

            std::cout << "hello " << myName << ", this is my lambda function callback. got param value: " << (int)myParam1 << std::endl;

            return true;
        }
    }};



    ////////////////////////////////////////
    //           SUB MENUES
    ////////////////////////////////////////

    dbg::SubMenu mySubMenu1 {{
        .Name = "Bibi",
        .Description = "Lo Aya Klum Ki Ein Klum",
        .Commands = {
                cmd1
        }
    }};



    ////////////////////////////////////////
    //            MY MENU
    ////////////////////////////////////////

    dbg::Menu myMenu{{
        .Name = "MyOtherMenu",
        .Description = "Office Of Prime Minister",
        .SubMenus = {
                mySubMenu1
        }
    }};

    return myMenu;

} // end of LoadDebugMenu() function
