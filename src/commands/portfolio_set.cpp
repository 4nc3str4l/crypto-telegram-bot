#include "portfolio_set.h"

#include <fmt/core.h>
#include "../portfolio_manager.h"
#include "../constants.h"


PortfolioSet::PortfolioSet(TgBot::Bot& bot, const std::int64_t chatId) :
Command(COMMAND_PORTFOLIO_SET, 3, bot, chatId){
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
    unsigned long id = getUnsignedLong();
    double quantity = getDouble();
    std::string ticker = getTicker();

    if(!PortfolioManager::shared_instance().isOwnerOf(m_chatId, id))
    {
        send(fmt::format("Could not find portfolio with id {}", id));
        return;
    }
    PortfolioManager::shared_instance().setAsset(ticker, quantity, id);
    send(fmt::format("Asset for portfolio {} set to {}{}", id, quantity, ticker));
}