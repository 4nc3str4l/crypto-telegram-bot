#include "portfolio_delete.h"
#include <fmt/core.h>
#include "../portfolio_manager.h"
#include "../constants.h"


PortfolioDelete::PortfolioDelete(TgBot::Bot& bot, const std::int64_t chatId) :
PortfolioCommand(COMMAND_PORTFOLIO_DELETE, 1, bot, chatId){
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
    if(!getPortfolioId()){
        return;
    }

    PortfolioManager::shared_instance().removePortfolio(m_Id, m_chatId);
    send(fmt::format("Portfolio with id={} deleted", m_Id));
}