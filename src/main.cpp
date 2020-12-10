#include <iostream>
#include <tgbot/tgbot.h>
#include <string>
#include <fmt/core.h>
#include <cstdint>

#include "price_checker.h"
#include "price_watcher.h"
#include "command_parsing.h"
#include "scripting/scripting.h"


int main(int argc, char *argv[])
{

    if (argc != 3)
    {
        std::cout << "Invalid number or arguments" << std::endl;
        return 1;
    }

    std::string telegramKey(argv[1]);
    PriceChecker::shared_instance().setApiKey(std::string(argv[2]));
    TgBot::Bot bot(telegramKey);
    Command::setupTgBot(bot);

    // Start the price watcher
    PriceWatcher::shared_instance().start(&bot);

    // Configure the LUA scripting system
    setupLua();

    bot.getEvents().onAnyMessage([&bot](TgBot::Message::Ptr message) {
        parseMessage(message->text, message->chat->id);
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
