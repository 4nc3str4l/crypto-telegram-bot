#include "./scripting.h"

#include <tgbot/tgbot.h>
#include "tgbot/types/GenericReply.h"

#include <sol/sol.hpp>
#include <fmt/core.h>
#include <vector>

#include "../price_checker.h"

#include "../commands/command.h"

void setupLua()
{
    sol::state lua{};
    lua.open_libraries(sol::lib::base);
    lua.set_function("check_price", &checkPrice);
    lua.set_function("send_message", &sendMessage);
    
    lua.script_file("lua_commands/price.lua");
    const std::function<void(const std::string, const std::int64_t)>& commandLogic = lua["logic"];
    //commandLogic("/price btc", "<>");
}

double checkPrice(const std::string& ticker)
{
    return PriceChecker::shared_instance().fetchPrice(ticker);
}

double sendMessage(const std::string& message, const std::int64_t chatId)
{
    Command::ssend(message, chatId);
}