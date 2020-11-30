#pragma once

#include "portfolio.h"

class PortfolioInversionIncrease : public PortfolioCommand
{
public:
    PortfolioInversionIncrease(TgBot::Bot& bot, const std::int64_t chatId);
    ~PortfolioInversionIncrease();
protected:
    void sendInstructions();
    const std::string getDescription();
    void commandLogic();
};