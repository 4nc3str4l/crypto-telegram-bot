#pragma once

#include "command.h"

class PortfolioDecrease : public Command
{
public:
    PortfolioDecrease(TgBot::Bot& bot, const std::int64_t chatId);
    ~PortfolioDecrease();
protected:
    void sendInstructions();
    const std::string getDescription();
    void commandLogic();
};