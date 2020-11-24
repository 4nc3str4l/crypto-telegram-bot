#pragma once

#include "command.h"

class PriceCommand : public Command
{
public:
    PriceCommand(TgBot::Bot& bot, const std::int64_t chatId);
    ~PriceCommand();
protected:
    void sendInstructions();
    const std::string getDescription();
    void commandLogic();
};