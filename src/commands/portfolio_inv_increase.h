#pragma once

#include "command.h"

class PortfolioInversionIncrease : public Command
{
public:
    PortfolioInversionIncrease(TgBot::Bot& bot, const std::int64_t chatId);
    ~PortfolioInversionIncrease();
protected:
    void sendInstructions();
    const std::string getDescription();
    void commandLogic();
};