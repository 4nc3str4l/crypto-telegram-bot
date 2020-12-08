#include "portfolio_inv_increase.h"
#include <fmt/core.h>
#include "../portfolio_manager.h"
#include "../constants.h"

PortfolioInversionIncrease::PortfolioInversionIncrease(TgBot::Bot &bot, const std::int64_t chatId) : PortfolioCommand(COMMAND_PORTFOLIO_INV_INCREASE, 2, bot, chatId)
{
}

void PortfolioInversionIncrease::sendInstructions()
{
    send(fmt::format("Invalid Command usage {} <>. Example: {} ada", m_command, m_command));
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
    if (!getPortfolioId())
    {
        return;
    }

    double invested = getDouble();
    portfolio p = PortfolioManager::shared_instance().getPortfolio(m_Id).value();
    double lastInvested = p.invested;
    double newInvested = p.invested + invested;
    newInvested = newInvested <= 0 ? 0 : newInvested;
    PortfolioManager::shared_instance().updateInvested(m_Id, newInvested);
    send(fmt::format("Portfolio {} with id {} invested set from {}{} to {}{}.",
                     p.name, p.id, lastInvested, CURRENCY_TICKER, newInvested, CURRENCY_TICKER));
}