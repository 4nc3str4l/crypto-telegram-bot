#include "portfolio_set.h"

#include <fmt/core.h>
#include "../portfolio_manager.h"
#include "../constants.h"

PortfolioSet::PortfolioSet(const std::int64_t chatId) : PortfolioCommand(COMMAND_PORTFOLIO_SET, 3, chatId)
{
}

void PortfolioSet::sendInstructions()
{
    send(fmt::format("Invalid Command usage {} <p_id> <quantity> <ticker>. Example: {} 1 100 ADA", m_command, m_command));
}

const std::string PortfolioSet::getDescription()
{
    return std::string("Sets the ammount of a current asset for a portfolio.");
}

PortfolioSet::~PortfolioSet()
{
}

void PortfolioSet::commandLogic()
{
    if (!getPortfolioId())
    {
        return;
    }

    double quantity = getDouble();
    std::string ticker = getTicker();
    if (ticker.size() == 0)
    {
        return;
    }

    PortfolioManager::shared_instance().setAsset(ticker, quantity, m_Id);
    send(fmt::format("Asset for portfolio {} set to {}{}", m_Id, quantity, ticker));
}