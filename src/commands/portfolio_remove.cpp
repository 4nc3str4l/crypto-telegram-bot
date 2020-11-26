#include "portfolio_remove.h"
#include <fmt/core.h>
#include "../price_checker.h"
#include "../constants.h"


PortfolioRemove::PortfolioRemove(TgBot::Bot& bot, const std::int64_t chatId) :
Command(COMMAND_PORTFOLIO_REMOVE, 1, bot, chatId){
}

void PortfolioRemove::sendInstructions()
{
    send(fmt::format("Invalid Command usage /{} <>. Example: /{} ada", m_command, m_command));
}

const std::string PortfolioRemove::getDescription()
{
    return std::string("Checks the price of a given asset.");
}

PortfolioRemove::~PortfolioRemove()
{

}

void PortfolioRemove::commandLogic()
{
   send(fmt::format("Command not implemented yet"));
}