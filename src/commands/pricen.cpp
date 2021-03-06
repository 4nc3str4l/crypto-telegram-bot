#include "pricen.h"
#include <fmt/core.h>

#include "../price_checker.h"
#include "../constants.h"
#include "../utils.h"

PricenCommand::PricenCommand(const std::int64_t chatId) : Command(COMMAND_PRICEN, 2, chatId)
{
}

void PricenCommand::sendInstructions()
{
    send(fmt::format("Invalid Command usage {} <ammount> <ticker>. Example: {} 10 ada", m_command, m_command));
}

const std::string PricenCommand::getDescription()
{
    return std::string("Checks the price of n tokens of the given asset.");
}

PricenCommand::~PricenCommand()
{
}

void PricenCommand::commandLogic()
{
    double quantity = getDouble();
    std::string ticker = getTicker();
    if (ticker.size() == 0)
    {
        return;
    }
    double price = PriceChecker::shared_instance().fetchPrice(ticker);
    double nPrice = price * quantity;
    if (price != -1)
    {
        send(fmt::format("Price of {} {} is {}{}", quantity, ticker, roundTo(nPrice, 2), CURRENCY_TICKER));
    }
    else
    {
        send(fmt::format("Could not check price of {}", ticker));
    }
}