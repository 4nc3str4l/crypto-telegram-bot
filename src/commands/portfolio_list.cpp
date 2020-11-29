#include "portfolio_list.h"
#include <fmt/core.h>
#include "../portfolio_manager.h"
#include "../constants.h"


PortfolioList::PortfolioList(TgBot::Bot& bot, const std::int64_t chatId) :
Command(COMMAND_PORTFOLIO_LIST, 0, bot, chatId){
}

void PortfolioList::sendInstructions()
{
    send(fmt::format("Invalid Command usage {}. Example: {}", m_command, m_command));
}

const std::string PortfolioList::getDescription()
{
    return std::string("Returns a list with all portfolios.");
}

PortfolioList::~PortfolioList()
{

}

void PortfolioList::commandLogic()
{
   send(PortfolioManager::shared_instance().listPortfolios(m_chatId));
}