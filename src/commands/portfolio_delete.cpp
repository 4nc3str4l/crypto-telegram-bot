#include "portfolio_delete.h"
#include <fmt/core.h>
#include "../portfolio_manager.h"
#include "../constants.h"


PortfolioDelete::PortfolioDelete(TgBot::Bot& bot, const std::int64_t chatId) :
Command(COMMAND_PORTFOLIO_DELETE, 1, bot, chatId){
}

void PortfolioDelete::sendInstructions()
{
    send(fmt::format("Invalid Command usage {} <portfolio_id>. Example: {} 1", m_command, m_command));
}

const std::string PortfolioDelete::getDescription()
{
    return std::string("Deletes a portfolio");
}

PortfolioDelete::~PortfolioDelete()
{

}

void PortfolioDelete::commandLogic()
{
    unsigned long pid = getUnsignedLong();

    if(!PortfolioManager::shared_instance().isOwnerOf(m_chatId, pid))
    {
        send(fmt::format("Could not find portfolio with id {}", pid));
        return;
    }

    PortfolioManager::shared_instance().removePortfolio(pid, m_chatId);
    send(fmt::format("Portfolio with id={} deleted", pid));
}