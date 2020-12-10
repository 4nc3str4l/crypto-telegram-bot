#include "help.h"
#include <fmt/core.h>
#include "../price_checker.h"
#include "../constants.h"

HelpCommand::HelpCommand(const std::int64_t chatId) : Command(COMMAND_HELP, 0, chatId)
{
}

void HelpCommand::sendInstructions()
{
    send(fmt::format("Invalid Command usage {} <>. Example: {} ada", m_command, m_command));
}

const std::string HelpCommand::getDescription()
{
    return std::string("Checks the price of a given asset.");
}

HelpCommand::~HelpCommand()
{
}

void HelpCommand::commandLogic()
{
    send(std::string(
        "*Command List:*\n"
        "*/conv:* Converts from a currency amount to another.\n"
        "*/help:* Legend of commands.\n"
        "*/pcheck:* Returns how much money is invested on a given portfolio.\n"
        "*/pdec:* Decrements the ammount of a current asset for a portfolio\n"
        "*/pdel:* Deletes a portfolio.\n"
        "*/pinc:* Increments the ammount of a current asset for a portfolio\n"
        "*/pinvdec:* Decreases the amount of money invested on a portfolio.\n"
        "*/pinvinc:* Increases the amount of money inested on portfolio.\n"
        "*/pinvset:* Sets the amount of money inested in portfolio.\n"
        "*/plist:* Returns a list with all portfolios.\n"
        "*/pnew:* Creates a new portfolio (avoid using spaces).\n"
        "*/prem:* Removes an asset from a portfolio.\n"
        "*/price:* Checks the price of a given asset.\n"
        "*/pricen:* Checks the price of N tokens of a given asset.\n"
        "*/pset:* Sets the ammount of a current asset for a portfolio.\n"
        "*/r:* Repeats the last successfull command.\n"
        "*/repeat:* Repeats the last successfull command.\n"
        "*/tconv:* Sets an alarm when a certain conversion rate is reached.\n"
        "*/tconvcheck:* Check the status of a convertion.\n"
        "*/tconvdel:* Stops a tracking alarm.\n"
        "*/tconvlist:* Lists convertions being tracked.\n"));
}