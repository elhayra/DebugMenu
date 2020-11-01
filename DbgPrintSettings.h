

#ifndef DEBUG_MENU_DBGPRINTSETTINGS_H
#define DEBUG_MENU_DBGPRINTSETTINGS_H


// format:
//
//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
//                             Menu
//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
//                this is the menu description
//
//
//=========================== Sub Menu =================================
//[1]-hello     [2]-SomeCommandIWrote   [3]-SudoAllUsers   [4]-BestDebug
//[5]-MyDebug   [6]-exampleDebug
//
//======================================================================
//
//=========================== Sub Menu =================================
//[1]-hello     [2]-SomeCommandIWrote   [3]-SudoAllUsers   [4]-BestDebug
//[5]-MyDebug   [6]-exampleDebug
//
//======================================================================
//
//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||


#define DBG_NUM_CMD_IN_ROW          3
#define DBG_NUM_CMD_SPACE_CHRS      3

#define DBG_SUB_MENU_BORDER_CHAR    '='
#define DBG_MENU_BORDER             '|'

// min chars to put before and after
// the sub-menu name. This will also determine
// the min width along with the sub-menu name
#define DBG_MIN_PRE_POST_BORDER_NAME_CHARS   3


#endif //DEBUG_MENU_DBGPRINTSETTINGS_H
