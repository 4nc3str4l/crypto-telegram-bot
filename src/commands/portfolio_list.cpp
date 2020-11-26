#include "portfolio_list.h"
#include <fmt/core.h>
#include "../price_checker.h"
#include "../constants.h"


PortfolioList::PortfolioList(TgBot::Bot& bot, const std::int64_t chatId) :
Command(COMMAND_PORTFOLIO_LIST, 1, bot, chatId){
}

void PortfolioList::sendInstructions()
{
    send(fmt::format("Invalid Command usage /{} <>. Example: /{} ada", m_command, m_command));
}

const std::string PortfolioList::getDescription()
{
    return std::string("Checks the price of a given asset.");
}

PortfolioList::~PortfolioList()
{

}

void PortfolioList::commandLogic()
{
   send(fmt::format("Command not implemented yet"));
}