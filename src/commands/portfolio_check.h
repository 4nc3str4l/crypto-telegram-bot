#pragma once

#include "portfolio.h"

class PortfolioCheck : public PortfolioCommand
{
public:
    PortfolioCheck(TgBot::Bot &bot, const std::int64_t chatId);
    ~PortfolioCheck();

protected:
    void sendInstructions();
    const std::string getDescription();
    void commandLogic();
};