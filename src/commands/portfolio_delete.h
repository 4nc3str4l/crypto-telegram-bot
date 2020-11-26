#pragma once

#include "command.h"

class PortfolioDelete : public Command
{
public:
    PortfolioDelete(TgBot::Bot& bot, const std::int64_t chatId);
    ~PortfolioDelete();
protected:
    void sendInstructions();
    const std::string getDescription();
    void commandLogic();
};