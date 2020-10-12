

#include "MyExampleDebugMenu.h"

#include "DbgMenu.h"
#include "DbgParamsParser.h"


#include <iostream>

//todo: try to make the command structures simpler to use and write - first think how I want it to look like

// == features ==
// all declarations are done in place - no need to declare in header file
// easy to use arguments parsing functions
// valid number of params is checked automatically
// automatic "pretty printer" including spacing, padding, headlines and extendable screen width


void f() {
    std::cout << "this is regular callback function" << std::endl;
}

dbg::Menu MyExampleDebugMenu::LoadDebugMenu() {




    ////////////////////////////////////////
    //           COMMANDS
    ////////////////////////////////////////

    // define commands
    dbg::Command cmd1{
            "command 1 name",
            "command 1 description",
            { //params list
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
            []() { //callback
                std::cout << "we have " << (int)dbg::GetNumOfParams() << " params available" << std::endl;

                //no need to check the num of params, this is done automatically.
                uint8_t myParam1 = dbg::GetParam<uint8_t>(); // get uint8_t param
                std::string myName = dbg::GetParam<std::string>();

                std::cout << "hello " << myName << ", this is my lambda function callback. got param value: " << (int)myParam1 << std::endl;
            }
    };

    dbg::Command cmd2{
            "command 2 name",
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

    dbg::Command cmd3{
            "123",
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

    dbg::Command cmd4{
            "12666666666666666666666666666666666666666666666666666666666",
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
            "12345",
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
            "My submenu1 name",
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
            "My submenu2 name",
            "my submenu2 description",
            {
                
            }
    };

    ////////////////////////////////////////
    //            MY MENU
    ////////////////////////////////////////

    dbg::Menu myMenu{
            "MY Menu name",
            "my menu description",
            {
                    mySubMenu1,
                    mySubMenu2
            }
    };

    std::cout << myMenu;

    return myMenu;

} // end of LoadDebugMenu() function
