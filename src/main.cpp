#include <iostream>
#include <tgbot/tgbot.h>
#include <string>
#include <fmt/core.h>
#include <cstdint>
#include <sol/sol.hpp>

#include "price_checker.h"
#include "price_watcher.h"
#include "command_parsing.h"

void lua_test()
{
    sol::state lua{};
    lua.open_libraries(sol::lib::base);
    lua.script_file("lua_commands/price.lua");
}

int main(int argc, char *argv[])
{

    lua_test();

    if (argc != 3)
    {
        std::cout << "Invalid number or arguments" << std::endl;
        return 1;
    }

    std::string telegramKey(argv[1]);
    PriceChecker::shared_instance().setApiKey(std::string(argv[2]));
    TgBot::Bot bot(telegramKey);

    // Start the price watcher
    PriceWatcher::shared_instance().start(&bot);

    bot.getEvents().onAnyMessage([&bot](TgBot::Message::Ptr message) {
        parseMessage(bot, message->text, message->chat->id);
    });

    try
    {
        printf("Bot username: %s\n", bot.getApi().getMe()->username.c_str());
        TgBot::TgLongPoll longPoll(bot);
        while (true)
        {
            longPoll.start();
        }
    }
    catch (TgBot::TgException &e)
    {
        printf("error: %s\n", e.what());
    }

    return 0;
}
