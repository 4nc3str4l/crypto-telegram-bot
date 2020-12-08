#include "portfolio_increase.h"
#include <fmt/core.h>
#include "../portfolio_manager.h"
#include "../constants.h"

PortfolioIncrease::PortfolioIncrease(TgBot::Bot &bot, const std::int64_t chatId) : PortfolioCommand(COMMAND_PORTFOLIO_INC, 3, bot, chatId)
{
}

void PortfolioIncrease::sendInstructions()
{
    send(fmt::format("Invalid Command usage {} <>. Example: {} ada", m_command, m_command));
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

    std::optional<asset> a = PortfolioManager::shared_instance().getPortfolioAsset(m_Id, ticker);
    if (!a.has_value())
    {
        PortfolioManager::shared_instance().setAsset(ticker, quantity, m_Id);
        send(fmt::format("Asset for portfolio {} set to {}{}", m_Id, quantity, ticker));
        return;
    }
    double lastQuantity = a.value().quantity;
    double newQuantity = lastQuantity + quantity;
    PortfolioManager::shared_instance().setAsset(ticker, newQuantity, m_Id);
    send(fmt::format("Asset for portfolio {} set from {}{} to {}{}", m_Id, lastQuantity, ticker, newQuantity, ticker));
}