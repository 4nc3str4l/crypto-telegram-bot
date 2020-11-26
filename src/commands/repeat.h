#pragma once

#include "command.h"

class RepeatCommand : public Command
{
public:
    RepeatCommand(TgBot::Bot& bot, const std::int64_t chatId);
    ~RepeatCommand();
protected:
    void sendInstructions();
    const std::string getDescription();
    void commandLogic();
};