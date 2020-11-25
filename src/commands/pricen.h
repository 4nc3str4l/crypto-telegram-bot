#pragma once

#include "command.h"

class PricenCommand : public Command
{
public:
    PricenCommand(TgBot::Bot& bot, const std::int64_t chatId);
    ~PricenCommand();
protected:
    void sendInstructions();
    const std::string getDescription();
    void commandLogic();
};