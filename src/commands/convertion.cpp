#include "convertion.h"

#include <fmt/core.h>
#include "../utils.h"
#include "../constants.h"

ConvertionCommand::ConvertionCommand(TgBot::Bot &bot, const std::int64_t chatId) : Command(COMMAND_CONV, 3, bot, chatId)
{
}

void ConvertionCommand::sendInstructions()
{
    send(fmt::format("Invalid Command usage {} <amount> <ticker> <target_ticker>. Example: {} 10 ada btc", m_command, m_command));
}

const std::string ConvertionCommand::getDescription()
{
    return std::string("Converts from a currency amount to another.");
}

ConvertionCommand::~ConvertionCommand()
{
}

void ConvertionCommand::commandLogic()
{
    double orAmount = getDouble();
    if (orAmount < 0)
    {
        send(fmt::format("Could not convert negative amounts"));
    }

    std::string ticker = getTicker();
    if (ticker.size() == 0)
    {
        return;
    }

    std::string targetTicker = getTicker();
    if (targetTicker.size() == 0)
    {
        return;
    }
    double convertion = computeConv(orAmount, ticker, targetTicker);

    if (convertion >= 0)
    {
        send(fmt::format("{} {} = {} {}", orAmount, ticker, roundTo(convertion, 2), targetTicker));
    }
    else
    {
        send(fmt::format("Could not compute the convertion for {} {}", ticker, targetTicker));
    }
}