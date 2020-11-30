#pragma once

#include "portfolio.h"

class PortfolioIncrease : public PortfolioCommand
{
public:
    PortfolioIncrease(TgBot::Bot &bot, const std::int64_t chatId);
    ~PortfolioIncrease();

protected:
    void sendInstructions();
    const std::string getDescription();
    void commandLogic();
};