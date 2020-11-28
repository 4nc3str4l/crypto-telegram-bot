#include <iostream>
#include <tgbot/tgbot.h>
#include <string>
#include <fmt/core.h>


#include "price_checker.h"
#include "price_watcher.h"
#include "data/persistence.h"
#include "constants.h"

#include "commands/price.h"
#include "commands/pricen.h"
#include "commands/convertion.h"
#include "commands/track_conv.h"
#include "commands/untrack_conv.h"
#include "commands/list_conv.h"
#include "commands/check_conv.h"

#include "commands/help.h"

#include "commands/portfolio_check.h"
#include "commands/portfolio_decrease.h"
#include "commands/portfolio_delete.h"
#include "commands/portfolio_increase.h"
#include "commands/portfolio_set.h"
#include "commands/portfolio_inv_decrease.h"
#include "commands/portfolio_inv_increase.h"
#include "commands/portfolio_inv_set.h"
#include "commands/portfolio_list.h"
#include "commands/portfolio_new.h"
#include "commands/portfolio_remove.h"
#include "commands/repeat.h"


const std::vector<std::string> getCommandArguments(const std::string &command)
{
    std::istringstream iss(command);
    std::vector<std::string> results((std::istream_iterator<std::string>(iss)),
                                     std::istream_iterator<std::string>());
    return results;
}


void exec(TgBot::Bot& bot, Command &c, TgBot::Message::Ptr message)
{
    if (!Persistence::shared_instance().isWhiteListed(message->from->id))
    {
        bot.getApi().sendMessage(message->chat->id, "Unauthorized");
        return;
    }
    c.execute(getCommandArguments(message->text));
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

    bot.getEvents().onCommand(COMMAND_PRICE, [&bot](TgBot::Message::Ptr message) {
        PriceCommand cmd(bot, message->chat->id);
        exec(bot, cmd, message);
    });

    bot.getEvents().onCommand(COMMAND_PRICEN, [&bot](TgBot::Message::Ptr message) {    
        PricenCommand cmd(bot, message->chat->id);
        exec(bot, cmd, message);
    });

    bot.getEvents().onCommand(COMMAND_CONV, [&bot](TgBot::Message::Ptr message) {    
        ConvertionCommand cmd(bot, message->chat->id);
        exec(bot, cmd, message);
    });

    bot.getEvents().onCommand(COMMAND_TRACK_CONV, [&bot](TgBot::Message::Ptr message) {    
        TrackConvertionCommand cmd(bot, message->chat->id);
        exec(bot, cmd, message);
    });

    bot.getEvents().onCommand(COMMAND_UNTRACK_CONV, [&bot](TgBot::Message::Ptr message) {    
        UnTrackConvertionCommand cmd(bot, message->chat->id);
        exec(bot, cmd, message);
    });

    bot.getEvents().onCommand(COMMAND_LIST_CONV, [&bot](TgBot::Message::Ptr message) {    
        ListTrackingConvertions cmd(bot, message->chat->id);
        exec(bot, cmd, message);
    });

    bot.getEvents().onCommand(COMMAND_CHECK_CONV, [&bot](TgBot::Message::Ptr message) {    
        ConvertionCheckCommand cmd(bot, message->chat->id);
        exec(bot, cmd, message);
    });

    bot.getEvents().onCommand(COMMAND_HELP, [&bot](TgBot::Message::Ptr message) {    
        HelpCommand cmd(bot, message->chat->id);
        exec(bot, cmd, message);
    });

    bot.getEvents().onCommand(COMMAND_PORTFOLIO_CHECK, [&bot](TgBot::Message::Ptr message) {    
        PortfolioCheck cmd(bot, message->chat->id);
        exec(bot, cmd, message);
    });

    bot.getEvents().onCommand(COMMAND_PORTFOLIO_DECREASE, [&bot](TgBot::Message::Ptr message) {    
        PortfolioDecrease cmd(bot, message->chat->id);
        exec(bot, cmd, message);
    });

    bot.getEvents().onCommand(COMMAND_PORTFOLIO_DELETE, [&bot](TgBot::Message::Ptr message) {    
        PortfolioDelete cmd(bot, message->chat->id);
        exec(bot, cmd, message);
    });

    bot.getEvents().onCommand(COMMAND_PORTFOLIO_INC, [&bot](TgBot::Message::Ptr message) {    
        PortfolioIncrease cmd(bot, message->chat->id);
        exec(bot, cmd, message);
    });

    bot.getEvents().onCommand(COMMAND_PORTFOLIO_SET, [&bot](TgBot::Message::Ptr message) {    
        PortfolioSet cmd(bot, message->chat->id);
        exec(bot, cmd, message);
    });

    bot.getEvents().onCommand(COMMAND_PORTFOLIO_INV_DECREASE, [&bot](TgBot::Message::Ptr message) {    
        PortfolioInversionDecrease cmd(bot, message->chat->id);
        exec(bot, cmd, message);
    });

    bot.getEvents().onCommand(COMMAND_PORTFOLIO_INV_INCREASE, [&bot](TgBot::Message::Ptr message) {    
        PortfolioInversionIncrease cmd(bot, message->chat->id);
        exec(bot, cmd, message);
    });

    bot.getEvents().onCommand(COMMAND_PORTFOLIO_INV_SET, [&bot](TgBot::Message::Ptr message) {    
        PortfolioInversionSet cmd(bot, message->chat->id);
        exec(bot, cmd, message);
    });

    bot.getEvents().onCommand(COMMAND_PORTFOLIO_LIST, [&bot](TgBot::Message::Ptr message) {    
        PortfolioList cmd(bot, message->chat->id);
        exec(bot, cmd, message);
    });

    bot.getEvents().onCommand(COMMAND_PORTFOLIO_NEW, [&bot](TgBot::Message::Ptr message) {    
        PortfolioNew cmd(bot, message->chat->id);
        exec(bot, cmd, message);
    });

    bot.getEvents().onCommand(COMMAND_PORTFOLIO_REMOVE, [&bot](TgBot::Message::Ptr message) {    
        PortfolioRemove cmd(bot, message->chat->id);
        exec(bot, cmd, message);
    });

    bot.getEvents().onCommand(COMMAND_REPEAT, [&bot](TgBot::Message::Ptr message) {    
        RepeatCommand cmd(bot, message->chat->id);
        exec(bot, cmd, message);
    });



    bot.getEvents().onAnyMessage([&bot](TgBot::Message::Ptr message) {
        // TODO: Reply with help command if text is not a valid command
        return;
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
