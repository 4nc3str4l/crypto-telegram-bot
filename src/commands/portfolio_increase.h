#pragma once

#include "command.h"

class PortfolioIncrease : public Command
{
public:
    PortfolioIncrease(TgBot::Bot& bot, const std::int64_t chatId);
    ~PortfolioIncrease();
protected:
    void sendInstructions();
    const std::string getDescription();
    void commandLogic();
};