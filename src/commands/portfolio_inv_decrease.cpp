#include "portfolio_inv_decrease.h"
#include <fmt/core.h>
#include "../portfolio_manager.h"
#include "../constants.h"


PortfolioInversionDecrease::PortfolioInversionDecrease(TgBot::Bot& bot, const std::int64_t chatId) :
Command(COMMAND_PORTFOLIO_INV_DECREASE, 2, bot, chatId){
}

void PortfolioInversionDecrease::sendInstructions()
{
    send(fmt::format("Invalid Command usage /{} <>. Example: /{} ada", m_command, m_command));
}

const std::string PortfolioInversionDecrease::getDescription()
{
    return std::string("Checks the price of a given asset.");
}

PortfolioInversionDecrease::~PortfolioInversionDecrease()
{

}

void PortfolioInversionDecrease::commandLogic()
{
    unsigned long pid = getUnsignedLong();
    double invested = getDouble(); 

    if(!PortfolioManager::shared_instance().isOwnerOf(m_chatId, pid))
    {
        send(fmt::format("Could not find portfolio with id {}", pid));
        return;
    }
    portfolio p = PortfolioManager::shared_instance().getPortfolio(pid);
    double lastInvested = p.invested;
    double newInvested = p.invested - invested;
    newInvested = newInvested <= 0 ? 0 : newInvested;
    PortfolioManager::shared_instance().updateInvested(pid, newInvested);
    send(fmt::format("Portfolio {} with id {} invested set from {}{} to {}{}.",
            p.name, p.id, lastInvested, CURRENCY_TICKER, newInvested, CURRENCY_TICKER));
}