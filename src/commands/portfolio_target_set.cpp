#include "portfolio_target_set.h"
#include <fmt/core.h>
#include "../constants.h"
#include "../portfolio_manager.h"

PortfolioTargetSet::PortfolioTargetSet(const std::int64_t chatId) : PortfolioCommand(COMMAND_PORTFOLIO_INV_SET, 2, chatId)
{
}

void PortfolioTargetSet::sendInstructions()
{
    send(fmt::format("Invalid Command usage {} <fiat_amount>. Example: {}", m_command, m_command));
}

const std::string PortfolioTargetSet::getDescription()
{
    return std::string("Sets how much money is expected to be made with the current portfolio");
}

PortfolioTargetSet::~PortfolioTargetSet()
{
}

void PortfolioTargetSet::commandLogic()
{
    if (!getPortfolioId())
    {
        return;
    }

    double target = getDouble();
    portfolio p = PortfolioManager::shared_instance().getPortfolio(m_Id).value();
    PortfolioManager::shared_instance().updateTarget(m_Id, target);
    double lasttarget = p.target;
    send(fmt::format("Portfolio {} with id {} target set from {}{} to {}{}.",
                     p.name, p.id, lasttarget, CURRENCY_TICKER, target, CURRENCY_TICKER));
}