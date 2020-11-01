

#include "MyExampleDebugMenu.h"

#include "DbgMenu.h"
#include "DbgParamsParser.h"


#include <iostream>




bool f() {
    std::cout << "this is regular callback function" << std::endl;
    return true;
}

dbg::Menu MyExampleDebugMenu::LoadDebugMenu() {




    ////////////////////////////////////////
    //           COMMANDS
    ////////////////////////////////////////

    // define commands
    dbg::Command cmd1{
            "LaunchRockets", // name
            "command 1 description", // description
            { //params list
                    { // param
                            "param 1 name",
                            "param1 descpription",
                            { //options list
                                    {"opt1 value", "opt1 name", "opt1 description"},
                                    {"opt2 value", "opt2 name"} // value description is optional
                            }
                    },
                    { // param

                            "param 2 name",
                            "param2 descpription"
                            // option list is optional
                    }
            },
            []() { //callback
                std::cout << "we have " << (int)dbg::GetNumOfParams() << " params available" << std::endl;

                //no need to check the num of params, this is done automatically.
                uint8_t myParam1 = dbg::GetParam<uint8_t>(); // get uint8_t param
                std::string myName = dbg::GetParam<std::string>();

                std::cout << "hello " << myName << ", this is my lambda function callback. got param value: " << (int)myParam1 << std::endl;

                return true;
            }
    };

    dbg::Command cmd2{
            "DoSomethingSillyPf",
            "command 2 description",
            { // params list
                    { //param1
                            "param 1 name",
                            "param1 descpription",
                            { //options list
                                    {"opt1 value", "opt1 name", "opt1 description"},
                                    {"opt2 value", "opt2 name"} // value description is optional
                            }
                    },
                    { // param2

                            "param 1 name",
                            "param1 descpription"
                            // option list is optional
                    }
            },
            []() {

                return dbg::cmd_ret_t{false, "something bad"};
            }
    };

    dbg::Command cmd3{
            "MySuperZevikCommand",
            "command 2 description",
            { // params list
                    { //param1
                            "param 1 name",
                            "param1 descpription",
                            { //options list
                                    {"opt1 value", "opt1 name", "opt1 description"},
                                    {"opt2 value", "opt2 name"} // value description is optional
                            }
                    },
                    { // param2

                            "param 1 name",
                            "param1 descpription"
                            // option list is optional
                    }
            },
            []() {
                return true;
            }
    };

    dbg::Command cmd4{
            "OverHeatCardToMax",
            "command 2 description",
            { // params list
                    { //param1
                            "param 1 name",
                            "param1 descpription",
                            { //options list
                                    {"opt1 value", "opt1 name", "opt1 description"},
                                    {"opt2 value", "opt2 name"} // value description is optional
                            }
                    },
                    { // param2

                            "param 1 name",
                            "param1 descpription"
                            // option list is optional
                    }
            },
            f  //regular function
    };

    dbg::Command cmd5{
            "MakeDevOpsScriptsRunSmoothly",
            "command 2 description",
            { // params list
                    { //param1
                            "param 1 name",
                            "param1 descpription",
                            { //options list
                                    {"opt1 value", "opt1 name", "opt1 description"},
                                    {"opt2 value", "opt2 name"} // value description is optional
                            }
                    },
                    { // param2

                            "param 1 name",
                            "param1 descpription"
                            // option list is optional
                    }
            },
            f  //regular function
    };


    dbg::Command cmd6{
            "ConvertCaffeToCode",
            "command 2 description",
            { // params list
                    { //param1
                            "param 1 name",
                            "param1 descpription",
                            { //options list
                                    {"opt1 value", "opt1 name", "opt1 description"},
                                    {"opt2 value", "opt2 name"} // value description is optional
                            }
                    },
                    { // param2

                            "param 1 name",
                            "param1 descpription"
                            // option list is optional
                    }
            },
            f  //regular function
    };


    dbg::Command cmd7{
            "HackerMode",
            "command 2 description",
            { // params list
                    { //param1
                            "param 1 name",
                            "param1 descpription",
                            { //options list
                                    {"opt1 value", "opt1 name", "opt1 description"},
                                    {"opt2 value", "opt2 name"} // value description is optional
                            }
                    },
                    { // param2

                            "param 1 name",
                            "param1 descpription"
                            // option list is optional
                    }
            },
            f  //regular function
    };


    ////////////////////////////////////////
    //           SUB MENUES
    ////////////////////////////////////////

    dbg::SubMenu mySubMenu1 {
            "PutinMenu",
            "my submenu1 description",
            {
                cmd1,
                cmd2,
                cmd3,
                cmd4,
                cmd5
            }
    };

    dbg::SubMenu mySubMenu2 {
            "TuringMachine",
            "my submenu2 description",
            {
                cmd6,
                cmd7
            }
    };

    dbg::SubMenu mySubMenu3 {
            "MyMenuWithNothing",
            "my submenu2 description",
            {

            }
    };


    ////////////////////////////////////////
    //            MY MENU
    ////////////////////////////////////////

    dbg::Menu myMenu{
            "MyMenu",
            "my menu description",
            {
                    mySubMenu1,
                    mySubMenu2,
                    mySubMenu3
            }
    };

    return myMenu;

} // end of LoadDebugMenu() function
