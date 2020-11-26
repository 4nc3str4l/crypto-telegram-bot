#include "portfolio_decrease.h"
#include <fmt/core.h>
#include "../price_checker.h"
#include "../constants.h"


PortfolioDecrease::PortfolioDecrease(TgBot::Bot& bot, const std::int64_t chatId) :
Command(COMMAND_PORTFOLIO_DECREASE, 1, bot, chatId){
}

void PortfolioDecrease::sendInstructions()
{
    send(fmt::format("Invalid Command usage /{} <>. Example: /{} ada", m_command, m_command));
}

const std::string PortfolioDecrease::getDescription()
{
    return std::string("Checks the price of a given asset.");
}

PortfolioDecrease::~PortfolioDecrease()
{

}

void PortfolioDecrease::commandLogic()
{
   send(fmt::format("Command not implemented yet"));
}