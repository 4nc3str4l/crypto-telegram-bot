#pragma once

#include "command.h"

class PortfolioList : public Command
{
public:
    PortfolioList(TgBot::Bot &bot, const std::int64_t chatId);
    ~PortfolioList();

protected:
    void sendInstructions() override;
    const std::string getDescription() override;
    void commandLogic() override;
};