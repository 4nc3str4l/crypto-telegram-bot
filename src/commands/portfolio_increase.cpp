#include "portfolio_increase.h"
#include <fmt/core.h>
#include "../portfolio_manager.h"
#include "../constants.h"


PortfolioIncrease::PortfolioIncrease(TgBot::Bot& bot, const std::int64_t chatId) :
Command(COMMAND_PORTFOLIO_INC, 1, bot, chatId){
}

void PortfolioIncrease::sendInstructions()
{
    send(fmt::format("Invalid Command usage /{} <>. Example: /{} ada", m_command, m_command));
}

const std::string PortfolioIncrease::getDescription()
{
    return std::string("Checks the price of a given asset.");
}

PortfolioIncrease::~PortfolioIncrease()
{

}

void PortfolioIncrease::commandLogic()
{
   send(fmt::format("Command not implemented yet"));
}