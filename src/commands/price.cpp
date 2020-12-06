#include "price.h"
#include <fmt/core.h>
#include "../price_checker.h"
#include "../constants.h"
#include "../utils.h"

PriceCommand::PriceCommand(TgBot::Bot &bot, const std::int64_t chatId) : Command(COMMAND_PRICE, 1, bot, chatId)
{
}

void PriceCommand::sendInstructions()
{
    send(fmt::format("Invalid Command usage {} <ticker>. Example: {} ada", m_command, m_command));
}

const std::string PriceCommand::getDescription()
{
    return std::string("Checks the price of a given asset.");
}

PriceCommand::~PriceCommand()
{
}

void PriceCommand::commandLogic()
{
    std::string ticker = getTicker();
    if (ticker.size() == 0)
    {
        return;
    }
    double price = PriceChecker::shared_instance().fetchPrice(ticker);
    if (price != -1)
    {
        send(fmt::format("Price of {} is {}{}", ticker, roundTo(price, 2), CURRENCY_TICKER));
    }
    else
    {
        send(fmt::format("Could not check price of {}", ticker));
    }
}