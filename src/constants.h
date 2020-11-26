#pragma once

#define DEBUG_MODE 0

// PRICE AND CONVERTION CHECK
#define COMMAND_PRICE                   "price"
#define COMMAND_PRICEN                  "pricen"
#define COMMAND_CONV                    "conv"

// CONVERTION TRACKING
#define COMMAND_TRACK_CONV              "tconv"
#define COMMAND_UNTRACK_CONV            "tconvdel"
#define COMMAND_LIST_CONV               "tconvlist"
#define COMMAND_CHECK_CONV              "tconvcheck"

// PORTFOLIO MANAGEMENT
#define COMMAND_PORTFOLIO_CHECK         "pcheck"
#define COMMAND_PORTFOLIO_DECREASE      "pdec"
#define COMMAND_PORTFOLIO_DELETE        "pdel"
#define COMMAND_PORTFOLIO_INC           "pinc"
#define COMMAND_PORTFOLIO_INV_DECREASE  "pinvdec"
#define COMMAND_PORTFOLIO_INV_INCREASE  "pinvinc"
#define COMMAND_PORTFOLIO_INV_SET       "pinvset"
#define COMMAND_PORTFOLIO_LIST          "plist"
#define COMMAND_PORTFOLIO_NEW           "pnew"
#define COMMAND_PORTFOLIO_REMOVE        "prem"

// HELP AND MYSC
#define COMMAND_HELP                    "help"

#define COMMAND_REPEAT_SHORT            "r"
#define COMMAND_REPEAT                  "repeat"

// OPERATIONS
#define UNAUTHORIZED_OPERATION 1
#define NOT_FOUND 2
#define OK 3

//#define CURRENCY "EUR"
//#define CURRENCY_TICKER "€"

#define CURRENCY "USD"
#define CURRENCY_TICKER "$"

// #define CURRENCY "CHF"
// #define CURRENCY_TICKER "CHF"
