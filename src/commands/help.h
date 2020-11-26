#pragma once

#include "command.h"

class HelpCommand : public Command
{
public:
    HelpCommand(TgBot::Bot& bot, const std::int64_t chatId);
    ~HelpCommand();
protected:
    void sendInstructions();
    const std::string getDescription();
    void commandLogic();
};