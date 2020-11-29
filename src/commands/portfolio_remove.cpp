#include "portfolio_remove.h"
#include <fmt/core.h>
#include "../portfolio_manager.h"
#include "../constants.h"


PortfolioRemove::PortfolioRemove(TgBot::Bot& bot, const std::int64_t chatId) :
Command(COMMAND_PORTFOLIO_REMOVE, 2, bot, chatId){
}

void PortfolioRemove::sendInstructions()
{
    send(fmt::format("Invalid Command usage {} <portfolio_id> <ticker>. Example: {} 1 ada", m_command, m_command));
}

const std::string PortfolioRemove::getDescription()
{
    return std::string("Removed an asset from a portfolio");
}

PortfolioRemove::~PortfolioRemove()
{

}

void PortfolioRemove::commandLogic()
{
    unsigned long id = getUnsignedLong();
    std::string ticker = getTicker();

    if(!PortfolioManager::shared_instance().isOwnerOf(m_chatId, id))
    {
        send(fmt::format("Could not find portfolio with id {}", id));
        return;
    }

    asset a = PortfolioManager::shared_instance().getPortfolioAsset(id, ticker);
    if(a.quantity == INVALID_ASSET)
    {
        send(fmt::format("Asset not found"));
        return;
    }
    PortfolioManager::shared_instance().setAsset(ticker, 0, id);
    send(fmt::format("Asset {} for portfolio {} removed", ticker, id));
}