#pragma once

#include "command.h"

class PortfolioInversionDecrease : public Command
{
public:
    PortfolioInversionDecrease(TgBot::Bot& bot, const std::int64_t chatId);
    ~PortfolioInversionDecrease();
protected:
    void sendInstructions();
    const std::string getDescription();
    void commandLogic();
};