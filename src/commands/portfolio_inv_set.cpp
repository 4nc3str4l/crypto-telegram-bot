#include "portfolio_inv_set.h"
#include <fmt/core.h>
#include "../constants.h"
#include "../portfolio_manager.h"


PortfolioInversionSet::PortfolioInversionSet(TgBot::Bot& bot, const std::int64_t chatId) :
Command(COMMAND_PORTFOLIO_INV_SET, 1, bot, chatId){
}

void PortfolioInversionSet::sendInstructions()
{
    send(fmt::format("Invalid Command usage /{} <>. Example: /{} ada", m_command, m_command));
}

const std::string PortfolioInversionSet::getDescription()
{
    return std::string("Checks the price of a given asset.");
}

PortfolioInversionSet::~PortfolioInversionSet()
{

}

void PortfolioInversionSet::commandLogic()
{
   send(fmt::format("Command not implemented yet"));
}