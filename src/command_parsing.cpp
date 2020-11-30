#include "command_parsing.h"

#include "data/persistence.h"

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

#include "constants.h"

std::map<std::int64_t, std::string> lastMessage;

const std::vector<std::string> getCommandArguments(const std::string &command)
{
    std::istringstream iss(command);
    std::vector<std::string> results((std::istream_iterator<std::string>(iss)),
                                     std::istream_iterator<std::string>());
    return results;
}


void exec(TgBot::Bot& bot, Command &c, const std::int64_t& chatId, const std::string& message)
{
    if (!Persistence::shared_instance().isWhiteListed(chatId))
    {
        bot.getApi().sendMessage(chatId, "Unauthorized");
        return;
    }
    c.execute(getCommandArguments(message));
}

void parseMessage(TgBot::Bot& bot, std::string message, const std::int64_t& chatId)
{
    bool foundMessage = true;
    std::string command = getCommandArguments(message)[0];
    
    if(command == COMMAND_PRICE)
    {
        PriceCommand cmd(bot, chatId);
        exec(bot, cmd, chatId, message);
    }
    else if(command == COMMAND_PRICEN)
    {
        PricenCommand cmd(bot, chatId);
        exec(bot, cmd, chatId, message);
    }
    else if(command == COMMAND_CONV)
    {
        ConvertionCommand cmd(bot, chatId);
        exec(bot, cmd, chatId, message);
    }
    else if(command == COMMAND_TRACK_CONV)
    {
        TrackConvertionCommand cmd(bot, chatId);
        exec(bot, cmd, chatId, message);
    }
    else if(command == COMMAND_UNTRACK_CONV)
    {
        UnTrackConvertionCommand cmd(bot, chatId);
        exec(bot, cmd, chatId, message);
    }
    else if(command == COMMAND_LIST_CONV)
    {
        ListTrackingConvertions cmd(bot, chatId);
        exec(bot, cmd, chatId, message);
    }
    else if(command == COMMAND_CHECK_CONV)
    {
        ConvertionCheckCommand cmd(bot, chatId);
        exec(bot, cmd, chatId, message);
    }
    else if(command == COMMAND_HELP)
    {
        HelpCommand cmd(bot, chatId);
        exec(bot, cmd, chatId, message);
    }
    else if(command == COMMAND_PORTFOLIO_CHECK)
    {
        PortfolioCheck cmd(bot, chatId);
        exec(bot, cmd, chatId, message);
    }
    else if(command == COMMAND_PORTFOLIO_DECREASE)
    {
        PortfolioDecrease cmd(bot, chatId);
        exec(bot, cmd, chatId, message);
    }
    else if(command == COMMAND_PORTFOLIO_DELETE)
    {
        PortfolioDelete cmd(bot, chatId);
        exec(bot, cmd, chatId, message);
    }
    else if(command == COMMAND_PORTFOLIO_INC)
    {
        PortfolioIncrease cmd(bot, chatId);
        exec(bot, cmd, chatId, message);
    }
    else if(command == COMMAND_PORTFOLIO_SET)
    {
        PortfolioSet cmd(bot, chatId);
        exec(bot, cmd, chatId, message);
    }
    else if(command == COMMAND_PORTFOLIO_INV_DECREASE)
    {
        PortfolioInversionDecrease cmd(bot, chatId);
        exec(bot, cmd, chatId, message);
    }
    else if(command == COMMAND_PORTFOLIO_INV_INCREASE)
    {
        PortfolioInversionIncrease cmd(bot, chatId);
        exec(bot, cmd, chatId, message);
    }
    else if(command == COMMAND_PORTFOLIO_INV_SET)
    {
        PortfolioInversionSet cmd(bot, chatId);
        exec(bot, cmd, chatId, message);
    }
    else if(command == COMMAND_PORTFOLIO_LIST)
    {
        PortfolioList cmd(bot, chatId);
        exec(bot, cmd, chatId, message);
    }
    else if(command == COMMAND_PORTFOLIO_NEW)
    {
        PortfolioNew cmd(bot, chatId);
        exec(bot, cmd, chatId, message);
    }
    else if(command == COMMAND_PORTFOLIO_REMOVE)
    {
        PortfolioRemove cmd(bot, chatId);
        exec(bot, cmd, chatId, message);
    }
    else if(command == COMMAND_REPEAT ||
            command == COMMAND_REPEAT_SHORT)
    {
        if(lastMessage.find(chatId) == lastMessage.end())
        {
            bot.getApi().sendMessage(chatId, "Repeat command not available due to a server restart");
            return;
        }
        parseMessage(bot, lastMessage[chatId], chatId);
        foundMessage = false;
    }
    else
    {
        bot.getApi().sendMessage(chatId, "Command not found:");
        HelpCommand cmd(bot, chatId);
        exec(bot, cmd, chatId, message);
        return;
    }
    
    if(foundMessage)
    {
	    lastMessage[chatId] = message;
    }
}