#include "price_command.h"
#include <fmt/core.h>
#include "../price_checker.h"


PriceCommand::PriceCommand(TgBot::Bot& bot, const std::int64_t chatId) :
Command("price", 1, bot, chatId){
}

void PriceCommand::sendInstructions()
{
    send(fmt::format("Invalid Command usage /{} <>. Example: /{} ada", m_command, m_command));
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
    double price = PriceChecker::shared_instance().fetchPrice(ticker);
    if (price != -1)
    {
        send(fmt::format("Price of {} is {} €", ticker, price));
    }
    else
    {
        send(fmt::format("Could not check price of {}", ticker));
    }
}