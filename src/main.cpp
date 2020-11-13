#include <iostream>
#include <tgbot/tgbot.h>
#include <string>

#include "price_checker.h"
#include "data/persistence.h"

#include <fmt/core.h>

PriceChecker priceChecker;
Persistence persistence;

std::vector<std::string> getCommandArguments(const std::string &command)
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

    priceChecker.SetApiKey(std::string(argv[2]));

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
        std::vector<std::string> params = getCommandArguments(message->text);
        if (params.size() == 2)
        {
            std::string ticker = params[1];
            std::transform(ticker.begin(), ticker.end(), ticker.begin(), ::toupper);
            double price = priceChecker.FetchPrice(ticker);
            if (price != -1)
            {
                bot.getApi().sendMessage(message->chat->id,
                                         fmt::format("Price of {} is {} €", ticker, price));
            }
            else
            {
        bot.getApi().sendMessage(message->chat->id,
                                 fmt::format("Could not check price of {}", ticker));
            }
        }
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