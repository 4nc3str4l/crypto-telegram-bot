#include "portfolio_remove.h"
#include <fmt/core.h>
#include "../portfolio_manager.h"
#include "../constants.h"


PortfolioRemove::PortfolioRemove(TgBot::Bot& bot, const std::int64_t chatId) :
PortfolioCommand(COMMAND_PORTFOLIO_REMOVE, 2, bot, chatId){
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
    if(!getPortfolioId()){
        return;
    }

    std::string ticker = getTicker();
    asset a = PortfolioManager::shared_instance().getPortfolioAsset(m_Id, ticker);
    if(a.quantity == INVALID_ASSET)
    {
        send(fmt::format("Asset not found"));
        return;
    }
    PortfolioManager::shared_instance().setAsset(ticker, 0, m_Id);
    send(fmt::format("Asset {} for portfolio {} removed", ticker, m_Id));
}