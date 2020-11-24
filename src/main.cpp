#include <iostream>
#include <tgbot/tgbot.h>
#include <string>
#include <fmt/core.h>


#include "price_checker.h"
#include "price_watcher.h"
#include "data/persistence.h"
#include "constants.h"

#include "commands/price.h"
#include "commands/convertion.h"
#include "commands/track_conv.h"
#include "commands/untrack_conv.h"

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
    PriceChecker::shared_instance().setApiKey(std::string(argv[2]));
    TgBot::Bot bot(telegramKey);

    // Start the price watcher
    PriceWatcher::shared_instance().start(&bot);

    bot.getEvents().onCommand(COMMAND_START, [&bot](TgBot::Message::Ptr message) {
        std::cout << "User Id " << message->from->id << std::endl;
        if (!persistence.isWhiteListed(message->from->id))
        {
            bot.getApi().sendMessage(message->chat->id, "Unauthorized");
            return;
        }
        bot.getApi().sendMessage(message->chat->id, "Hi!");
    });

    bot.getEvents().onCommand(COMMAND_PRICE, [&bot](TgBot::Message::Ptr message) {    
        PriceCommand cmd(bot, message->chat->id);
        cmd.execute(getCommandArguments(message->text));
    });

    bot.getEvents().onCommand(COMMAND_CONV, [&bot](TgBot::Message::Ptr message) {    
        ConvertionCommand cmd(bot, message->chat->id);
        cmd.execute(getCommandArguments(message->text));
    });

    bot.getEvents().onCommand(COMMAND_TRACK_CONV, [&bot](TgBot::Message::Ptr message) {    
        TrackConvertionCommand cmd(bot, message->chat->id);
        cmd.execute(getCommandArguments(message->text));
    });

    bot.getEvents().onCommand(COMMAND_UNTRACK_CONV, [&bot](TgBot::Message::Ptr message) {    
        UnTrackConvertionCommand cmd(bot, message->chat->id);
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
