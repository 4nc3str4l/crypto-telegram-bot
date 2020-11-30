#include "portfolio.h"

#include <fmt/core.h>
#include "../portfolio_manager.h"
#include "../constants.h"

PortfolioCommand::PortfolioCommand(const std::string &name, const unsigned short numArguments, TgBot::Bot &bot, const std::int64_t chatId) : Command(name, numArguments, bot, chatId)
{
}

bool PortfolioCommand::getPortfolioId()
{
    unsigned long id = getUnsignedLong();
    if (!PortfolioManager::shared_instance().isOwnerOf(m_chatId, id))
    {
        send(fmt::format("Could not find portfolio with id {}", id));
        m_Id = INVALID_PORTFOLIO;
        return false;
    }
    m_Id = id;
    return true;
}

PortfolioCommand::~PortfolioCommand() {}