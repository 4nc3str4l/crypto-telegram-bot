#include "portfolio_remove.h"
#include <fmt/core.h>
#include "../portfolio_manager.h"
#include "../constants.h"


PortfolioRemove::PortfolioRemove(TgBot::Bot& bot, const std::int64_t chatId) :
Command(COMMAND_PORTFOLIO_REMOVE, 1, bot, chatId){
}

void PortfolioRemove::sendInstructions()
{
    send(fmt::format("Invalid Command usage /{} <>. Example: /{} ada", m_command, m_command));
}

const std::string PortfolioRemove::getDescription()
{
    return std::string("Checks the price of a given asset.");
}

PortfolioRemove::~PortfolioRemove()
{

}

void PortfolioRemove::commandLogic()
{
    unsigned long id = getUnsignedLong();
    if(!PortfolioManager::shared_instance().isOwnerOf(m_chatId, id))
    {
        send(fmt::format("Could not find portfolio with id {}", id));
        return;
    }
    send(fmt::format("Command not implemented yet"));
}