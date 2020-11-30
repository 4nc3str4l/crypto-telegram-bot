#include "portfolio_decrease.h"
#include <fmt/core.h>
#include "../portfolio_manager.h"
#include "../constants.h"

PortfolioDecrease::PortfolioDecrease(TgBot::Bot &bot, const std::int64_t chatId) : PortfolioCommand(COMMAND_PORTFOLIO_DECREASE, 3, bot, chatId)
{
}

void PortfolioDecrease::sendInstructions()
{
    send(fmt::format("Invalid Command usage {} <>. Example: {} ada", m_command, m_command));
}

const std::string PortfolioDecrease::getDescription()
{
    return std::string("Checks the price of a given asset.");
}

PortfolioDecrease::~PortfolioDecrease()
{
}

void PortfolioDecrease::commandLogic()
{
    if (!getPortfolioId())
    {
        return;
    }

    double quantity = getDouble();
    std::string ticker = getTicker();
    asset a = PortfolioManager::shared_instance().getPortfolioAsset(m_Id, ticker);
    if (a.quantity == INVALID_ASSET)
    {
        send(fmt::format("There is no {} in portfolio with id={}.", ticker, m_Id));
        return;
    }

    double lastQuantity = a.quantity;
    double newQuantity = lastQuantity - quantity;
    newQuantity = newQuantity < 0 ? 0 : newQuantity;
    PortfolioManager::shared_instance().setAsset(ticker, newQuantity, m_Id);
    send(fmt::format("Asset for portfolio {} set from {}{} to {}{}", m_Id, lastQuantity, ticker, newQuantity, ticker));
}