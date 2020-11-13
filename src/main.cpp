#include <iostream>
#include <tgbot/tgbot.h>
#include <string>

#include "price_checker.h"
#include "data/persistence.h"
#include "commands/price_command.h"

#include <fmt/core.h>

PriceChecker priceChecker;
Persistence persistence;

const std::vector<std::string> getCommandArguments(const std::string &command)
{
    std::istringstream iss(command);
    std::vector<std::string> results((std::istream_iterator<std::string>(iss)),
                                     std::istream_iterator<std::string>());
    return results;
}

int main(int argc, char *argv[])
{

    if (argc != 3)
    {
        std::cout << "Invalid number or arguments" << std::endl;
        return 1;
    }

    std::string telegramKey(argv[1]);

    priceChecker.setApiKey(std::string(argv[2]));

    TgBot::Bot bot(telegramKey);

    bot.getEvents().onCommand("start", [&bot](TgBot::Message::Ptr message) {
        std::cout << "User Id " << message->from->id << std::endl;
        if (!persistence.IsWhiteListed(message->from->id))
        {
            bot.getApi().sendMessage(message->chat->id, "Unauthorized");
            return;
        }
        bot.getApi().sendMessage(message->chat->id, "Hi!");
    });

    bot.getEvents().onCommand("price", [&bot](TgBot::Message::Ptr message) {    
        PriceCommand cmd(bot, message->chat->id, &priceChecker);
        cmd.execute(getCommandArguments(message->text));
    });

    bot.getEvents().onAnyMessage([&bot](TgBot::Message::Ptr message) {
        printf("User wrote %s\n", message->text.c_str());
        if (StringTools::startsWith(message->text, "/start") || StringTools::startsWith(message->text, "/price"))
        {
            return;
        }
        bot.getApi().sendMessage(message->chat->id, "Your message is: " + message->text);
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
