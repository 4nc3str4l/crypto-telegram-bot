#pragma once

#include "command.h"

class ConvertionCheckCommand : public Command
{
public:
    ConvertionCheckCommand(TgBot::Bot &bot, const std::int64_t chatId);
    ~ConvertionCheckCommand();

protected:
    void sendInstructions();
    const std::string getDescription();
    void commandLogic();
};