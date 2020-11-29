#include "portfolio_decrease.h"
#include <fmt/core.h>
#include "../portfolio_manager.h"
#include "../constants.h"


PortfolioDecrease::PortfolioDecrease(TgBot::Bot& bot, const std::int64_t chatId) :
Command(COMMAND_PORTFOLIO_DECREASE, 3, bot, chatId){
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
    unsigned long id = getUnsignedLong();
    double quantity = getDouble();
    std::string ticker = getTicker();

    if(!PortfolioManager::shared_instance().isOwnerOf(m_chatId, id))
    {
        send(fmt::format("Could not find portfolio with id {}", id));
        return;
    }

    asset a = PortfolioManager::shared_instance().getPortfolioAsset(id, ticker);
    if(a.quantity == INVALID_ASSET)
    {
        send(fmt::format("There is no {} in portfolio with id={}.", ticker, id));
        return;
    }

    double lastQuantity = a.quantity;
    double newQuantity = lastQuantity - quantity;
    newQuantity = newQuantity < 0 ? 0 : newQuantity;
    PortfolioManager::shared_instance().setAsset(ticker, newQuantity, id);
    send(fmt::format("Asset for portfolio {} set from {}{} to {}{}", id, lastQuantity, ticker, newQuantity, ticker));
}