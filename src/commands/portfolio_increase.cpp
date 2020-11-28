#include "portfolio_increase.h"
#include <fmt/core.h>
#include "../portfolio_manager.h"
#include "../constants.h"


PortfolioIncrease::PortfolioIncrease(TgBot::Bot& bot, const std::int64_t chatId) :
Command(COMMAND_PORTFOLIO_INC, 3, bot, chatId){
}

void PortfolioIncrease::sendInstructions()
{
    send(fmt::format("Invalid Command usage /{} <>. Example: /{} ada", m_command, m_command));
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
        PortfolioManager::shared_instance().setAsset(ticker, quantity, id);
        send(fmt::format("Asset for portfolio {} set to {}{}", id, quantity, ticker));
        return;
    }
    double lastQuantity = a.quantity;
    double newQuantity = lastQuantity + quantity;
    PortfolioManager::shared_instance().setAsset(ticker, newQuantity, id);
    send(fmt::format("Asset for portfolio {} set from {}{} to {}{}", id, lastQuantity, ticker, newQuantity, ticker));
}