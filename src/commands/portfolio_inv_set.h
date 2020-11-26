#pragma once

#include "command.h"

class PortfolioInversionSet : public Command
{
public:
    PortfolioInversionSet(TgBot::Bot& bot, const std::int64_t chatId);
    ~PortfolioInversionSet();
protected:
    void sendInstructions();
    const std::string getDescription();
    void commandLogic();
};