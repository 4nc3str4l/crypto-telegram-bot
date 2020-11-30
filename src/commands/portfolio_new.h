#pragma once

#include "command.h"

class PortfolioNew : public Command
{
public:
    PortfolioNew(TgBot::Bot &bot, const std::int64_t chatId);
    ~PortfolioNew();

protected:
    void sendInstructions();
    const std::string getDescription();
    void commandLogic();
};