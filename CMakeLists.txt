cmake_minimum_required(VERSION 3.13)
project(debug_menu)

set(CMAKE_CXX_STANDARD 11)

add_executable(debug_menu main.cpp DbgParamsParser.cpp DbgParamsParser.h DbgArgs.cpp DbgArgs.h DbgCommand.cpp DbgCommand.h DbgParam.cpp DbgParam.h DbgMenu.cpp DbgMenu.h DbgPrintableEntity.h DbgMainMenu.cpp DbgMainMenu.h DbgSubMenu.cpp DbgSubMenu.h MyExampleDebugMenu.cpp MyExampleDebugMenu.h DbgPrintSettings.h DbgPrintableEntity.cpp DbgUtil.cpp DbgUtil.h)