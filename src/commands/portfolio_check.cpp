#include "portfolio_check.h"
#include <fmt/core.h>
#include <optional>

#include "../portfolio_manager.h"
#include "../constants.h"
#include "../utils.h"

PortfolioCheck::PortfolioCheck(const std::int64_t chatId) : PortfolioCommand(COMMAND_PORTFOLIO_CHECK, 1, chatId)
{
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
    if (!getPortfolioId())
    {
        return;
    }
    std::optional<portfolio> p = PortfolioManager::shared_instance().getPortfolio(m_Id);
    send(getPorfolioInformation(p.value()));
}