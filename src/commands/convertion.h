#pragma once

#include "command.h"

class ConvertionCommand : public Command
{
public:
    ConvertionCommand(TgBot::Bot& bot, const std::int64_t chatId);
    ~ConvertionCommand();
protected:
    void sendInstructions();
    const std::string getDescription();
    void commandLogic();
};