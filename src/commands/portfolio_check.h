#pragma once

#include "command.h"

class PortfolioCheck : public Command
{
public:
    PortfolioCheck(TgBot::Bot& bot, const std::int64_t chatId);
    ~PortfolioCheck();
protected:
    void sendInstructions();
    const std::string getDescription();
    void commandLogic();
};