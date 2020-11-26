#include "portfolio_new.h"

#include <fmt/core.h>
#include "../constants.h"
#include "../portfolio_manager.h"

PortfolioNew::PortfolioNew(TgBot::Bot& bot, const std::int64_t chatId) :
Command(COMMAND_PORTFOLIO_NEW, 1, bot, chatId){
}

void PortfolioNew::sendInstructions()
{
    send(fmt::format("Invalid Command usage /{} <name>. Example: /{} staking", m_command, m_command));
}

const std::string PortfolioNew::getDescription()
{
    return std::string("Creates a new portfolio (avoid using spaces).");
}

PortfolioNew::~PortfolioNew()
{

}

void PortfolioNew::commandLogic()
{
    std::string name = getString();
    unsigned long id = PortfolioManager::shared_instance().addPortfolio(m_chatId, name);
    send(fmt::format("Created portfolio *{}* with id *{}*.", name, id));
}