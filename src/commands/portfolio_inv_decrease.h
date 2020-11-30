#pragma once

#include "portfolio.h"

class PortfolioInversionDecrease : public PortfolioCommand
{
public:
    PortfolioInversionDecrease(TgBot::Bot& bot, const std::int64_t chatId);
    ~PortfolioInversionDecrease();
protected:
    void sendInstructions();
    const std::string getDescription();
    void commandLogic();
};