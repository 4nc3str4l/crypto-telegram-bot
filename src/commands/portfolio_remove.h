#pragma once

#include "command.h"

class PortfolioRemove : public Command
{
public:
    PortfolioRemove(TgBot::Bot& bot, const std::int64_t chatId);
    ~PortfolioRemove();
protected:
    void sendInstructions();
    const std::string getDescription();
    void commandLogic();
};