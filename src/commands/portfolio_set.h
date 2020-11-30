#pragma once

#include "portfolio.h"

class PortfolioSet : public PortfolioCommand
{
public:
    PortfolioSet(TgBot::Bot& bot, const std::int64_t chatId);
    ~PortfolioSet();
protected:
    void sendInstructions();
    const std::string getDescription();
    void commandLogic();
};