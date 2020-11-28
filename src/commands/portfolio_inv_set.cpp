#include "portfolio_inv_set.h"
#include <fmt/core.h>
#include "../constants.h"
#include "../portfolio_manager.h"


PortfolioInversionSet::PortfolioInversionSet(TgBot::Bot& bot, const std::int64_t chatId) :
Command(COMMAND_PORTFOLIO_INV_SET, 2, bot, chatId){
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
    unsigned long pid = getUnsignedLong();
    double invested = getDouble(); 

    if(!PortfolioManager::shared_instance().isOwnerOf(m_chatId, pid))
    {
        send(fmt::format("Could not find portfolio with id {}", pid));
        return;
    }

    portfolio p = PortfolioManager::shared_instance().getPortfolio(pid);
    PortfolioManager::shared_instance().updateInvested(pid, invested);
    double lastInvested = p.invested;
    send(fmt::format("Portfolio {} with id {} invested set from {}{} to {}{}.",
            p.name, p.id, lastInvested, CURRENCY_TICKER, invested, CURRENCY_TICKER));
}