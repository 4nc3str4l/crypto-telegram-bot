#pragma once

#include "command.h"

class PortfolioSet : public Command
{
public:
    PortfolioSet(TgBot::Bot& bot, const std::int64_t chatId);
    ~PortfolioSet();
protected:
    void sendInstructions();
    const std::string getDescription();
    void commandLogic();
};