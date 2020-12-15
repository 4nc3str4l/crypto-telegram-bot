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

#include "scripting/scripting.h"

std::unordered_map<std::int64_t, std::string> lastMessage;

const std::vector<std::string> getCommandArguments(const std::string &command)
{
    std::istringstream iss(command);
    std::vector<std::string> results((std::istream_iterator<std::string>(iss)),
                                     std::istream_iterator<std::string>());
    return results;
}

void exec(Command &c, const std::int64_t chatId, const std::string &message)
{
    if (!Persistence::shared_instance().isWhiteListed(chatId))
    {
        Command::ssend("Unauthorized", chatId);
        return;
    }
    c.execute(getCommandArguments(message));
}

void parseMessage(const std::string& message, const std::int64_t chatId)
{
    bool foundMessage = true;
    std::string command = getCommandArguments(message)[0];

    if (command == COMMAND_PRICE)
    {
        PriceCommand cmd(chatId);
        exec(cmd, chatId, message);
    }
    else if (command == COMMAND_PRICEN)
    {
        PricenCommand cmd(chatId);
        exec(cmd, chatId, message);
    }
    else if (command == COMMAND_CONV)
    {
        ConvertionCommand cmd(chatId);
        exec(cmd, chatId, message);
    }
    else if (command == COMMAND_TRACK_CONV)
    {
        TrackConvertionCommand cmd(chatId);
        exec(cmd, chatId, message);
    }
    else if (command == COMMAND_UNTRACK_CONV)
    {
        UnTrackConvertionCommand cmd(chatId);
        exec(cmd, chatId, message);
    }
    else if (command == COMMAND_LIST_CONV)
    {
        ListTrackingConvertions cmd(chatId);
        exec(cmd, chatId, message);
    }
    else if (command == COMMAND_CHECK_CONV)
    {
        ConvertionCheckCommand cmd(chatId);
        exec(cmd, chatId, message);
    }
    else if (command == COMMAND_HELP)
    {
        HelpCommand cmd(chatId);
        exec(cmd, chatId, message);
    }
    else if (command == COMMAND_PORTFOLIO_CHECK)
    {
        PortfolioCheck cmd(chatId);
        exec(cmd, chatId, message);
    }
    else if (command == COMMAND_PORTFOLIO_DECREASE)
    {
        PortfolioDecrease cmd(chatId);
        exec(cmd, chatId, message);
    }
    else if (command == COMMAND_PORTFOLIO_DELETE)
    {
        PortfolioDelete cmd(chatId);
        exec(cmd, chatId, message);
    }
    else if (command == COMMAND_PORTFOLIO_INC)
    {
        PortfolioIncrease cmd(chatId);
        exec(cmd, chatId, message);
    }
    else if (command == COMMAND_PORTFOLIO_SET)
    {
        PortfolioSet cmd(chatId);
        exec(cmd, chatId, message);
    }
    else if (command == COMMAND_PORTFOLIO_INV_DECREASE)
    {
        PortfolioInversionDecrease cmd(chatId);
        exec(cmd, chatId, message);
    }
    else if (command == COMMAND_PORTFOLIO_INV_INCREASE)
    {
        PortfolioInversionIncrease cmd(chatId);
        exec(cmd, chatId, message);
    }
    else if (command == COMMAND_PORTFOLIO_INV_SET)
    {
        PortfolioInversionSet cmd(chatId);
        exec(cmd, chatId, message);
    }
    else if (command == COMMAND_PORTFOLIO_LIST)
    {
        PortfolioList cmd(chatId);
        exec(cmd, chatId, message);
    }
    else if (command == COMMAND_PORTFOLIO_NEW)
    {
        PortfolioNew cmd(chatId);
        exec(cmd, chatId, message);
    }
    else if (command == COMMAND_PORTFOLIO_REMOVE)
    {
        PortfolioRemove cmd(chatId);
        exec(cmd, chatId, message);
    }
    else if (command == COMMAND_REPEAT ||
             command == COMMAND_REPEAT_SHORT)
    {
        if (lastMessage.find(chatId) == lastMessage.end())
        {
            Command::ssend("Repeat command not available due to a server restart", chatId);
            return;
        }
        parseMessage(lastMessage[chatId], chatId);
        foundMessage = false;
    }
    else
    {
        // try to execute a LUA command
        if (!Persistence::shared_instance().isWhiteListed(chatId))
        {   
            Command::ssend("Unauthorized", chatId);
            return;
        }

        if(!Scripting::shared_instance().executeLuaCommand(command, getCommandArguments(message), chatId))
        {
            Command::ssend("Command not found:", chatId);
            HelpCommand cmd(chatId);
            exec(cmd, chatId, message);
            return;
        }

    }

    if (foundMessage)
    {
        lastMessage[chatId] = message;
    }
}