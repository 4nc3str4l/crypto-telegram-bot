#include "portfolio_inv_set.h"
#include <fmt/core.h>
#include "../constants.h"
#include "../portfolio_manager.h"


PortfolioInversionSet::PortfolioInversionSet(TgBot::Bot& bot, const std::int64_t chatId) :
PortfolioCommand(COMMAND_PORTFOLIO_INV_SET, 2, bot, chatId){
}

void PortfolioInversionSet::sendInstructions()
{
    send(fmt::format("Invalid Command usage {} <>. Example: {} ada", m_command, m_command));
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
    if(!getPortfolioId()){
        return;
    }

    double invested = getDouble(); 
    portfolio p = PortfolioManager::shared_instance().getPortfolio(m_Id);
    PortfolioManager::shared_instance().updateInvested(m_Id, invested);
    double lastInvested = p.invested;
    send(fmt::format("Portfolio {} with id {} invested set from {}{} to {}{}.",
            p.name, p.id, lastInvested, CURRENCY_TICKER, invested, CURRENCY_TICKER));
}