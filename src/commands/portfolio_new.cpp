#include "portfolio_new.h"
#include <fmt/core.h>
#include "../price_checker.h"
#include "../constants.h"


PortfolioNew::PortfolioNew(TgBot::Bot& bot, const std::int64_t chatId) :
Command(COMMAND_PORTFOLIO_NEW, 1, bot, chatId){
}

void PortfolioNew::sendInstructions()
{
    send(fmt::format("Invalid Command usage /{} <>. Example: /{} ada", m_command, m_command));
}

const std::string PortfolioNew::getDescription()
{
    return std::string("Checks the price of a given asset.");
}

PortfolioNew::~PortfolioNew()
{

}

void PortfolioNew::commandLogic()
{
   send(fmt::format("Command not implemented yet"));
}