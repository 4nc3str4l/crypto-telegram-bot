#include "repeat.h"
#include <fmt/core.h>
#include "../price_checker.h"
#include "../constants.h"


RepeatCommand::RepeatCommand(TgBot::Bot& bot, const std::int64_t chatId) :
Command(COMMAND_REPEAT, 1, bot, chatId){
}

void RepeatCommand::sendInstructions()
{
    send(fmt::format("Invalid Command usage /{} <>. Example: /{} ada", m_command, m_command));
}

const std::string RepeatCommand::getDescription()
{
    return std::string("Checks the price of a given asset.");
}

RepeatCommand::~RepeatCommand()
{

}

void RepeatCommand::commandLogic()
{
   send(fmt::format("Command not implemented yet"));
}