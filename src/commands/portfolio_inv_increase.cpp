#include "portfolio_inv_increase.h"
#include <fmt/core.h>
#include "../portfolio_manager.h"
#include "../constants.h"


PortfolioInversionIncrease::PortfolioInversionIncrease(TgBot::Bot& bot, const std::int64_t chatId) :
Command(COMMAND_PORTFOLIO_INV_INCREASE, 1, bot, chatId){
}

void PortfolioInversionIncrease::sendInstructions()
{
    send(fmt::format("Invalid Command usage /{} <>. Example: /{} ada", m_command, m_command));
}

const std::string PortfolioInversionIncrease::getDescription()
{
    return std::string("Checks the price of a given asset.");
}

PortfolioInversionIncrease::~PortfolioInversionIncrease()
{

}

void PortfolioInversionIncrease::commandLogic()
{
   send(fmt::format("Command not implemented yet"));
}