#pragma once

#include "portfolio.h"

class PortfolioRemove : public PortfolioCommand
{
public:
    PortfolioRemove(TgBot::Bot &bot, const std::int64_t chatId);
    ~PortfolioRemove();

protected:
    void sendInstructions();
    const std::string getDescription();
    void commandLogic();
};