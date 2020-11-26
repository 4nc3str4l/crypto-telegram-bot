#include "portfolio_delete.h"
#include <fmt/core.h>
#include "../price_checker.h"
#include "../constants.h"


PortfolioDelete::PortfolioDelete(TgBot::Bot& bot, const std::int64_t chatId) :
Command(COMMAND_PORTFOLIO_DELETE, 1, bot, chatId){
}

void PortfolioDelete::sendInstructions()
{
    send(fmt::format("Invalid Command usage /{} <>. Example: /{} ada", m_command, m_command));
}

const std::string PortfolioDelete::getDescription()
{
    return std::string("Checks the price of a given asset.");
}

PortfolioDelete::~PortfolioDelete()
{

}

void PortfolioDelete::commandLogic()
{
   send(fmt::format("Command not implemented yet"));
}