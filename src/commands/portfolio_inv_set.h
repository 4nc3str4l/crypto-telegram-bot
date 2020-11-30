#pragma once

#include "portfolio.h"

class PortfolioInversionSet : public PortfolioCommand
{
public:
    PortfolioInversionSet(TgBot::Bot& bot, const std::int64_t chatId);
    ~PortfolioInversionSet();
protected:
    void sendInstructions();
    const std::string getDescription();
    void commandLogic();
};