#include "portfolio_check.h"
#include <fmt/core.h>

#include "../portfolio_manager.h"
#include "../constants.h"
#include "../utils.h"


PortfolioCheck::PortfolioCheck(TgBot::Bot& bot, const std::int64_t chatId) :
Command(COMMAND_PORTFOLIO_CHECK, 1, bot, chatId){
}

void PortfolioCheck::sendInstructions()
{
    send(fmt::format("Invalid Command usage {} <id>. Example: {} 1", m_command, m_command));
}

const std::string PortfolioCheck::getDescription()
{
    return std::string("Returns the information about a given portfolio");
}

PortfolioCheck::~PortfolioCheck()
{

}

void PortfolioCheck::commandLogic()
{
    unsigned long id = getUnsignedLong();
    if(!PortfolioManager::shared_instance().isOwnerOf(m_chatId, id))
    {
        send(fmt::format("Could not find portfolio with id {}", id));
        return;
    }
    portfolio p = PortfolioManager::shared_instance().getPortfolio(id);
    send(getPorfolioInformation(p));
}