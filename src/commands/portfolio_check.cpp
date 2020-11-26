#include "portfolio_check.h"
#include <fmt/core.h>

#include "../portfolio_manager.h"
#include "../constants.h"


PortfolioCheck::PortfolioCheck(TgBot::Bot& bot, const std::int64_t chatId) :
Command(COMMAND_PORTFOLIO_CHECK, 1, bot, chatId){
}

void PortfolioCheck::sendInstructions()
{
    send(fmt::format("Invalid Command usage /{} <>. Example: /{} ada", m_command, m_command));
}

const std::string PortfolioCheck::getDescription()
{
    return std::string("Checks the price of a given asset.");
}

PortfolioCheck::~PortfolioCheck()
{

}

void PortfolioCheck::commandLogic()
{
   send(fmt::format("Command not implemented yet"));
}