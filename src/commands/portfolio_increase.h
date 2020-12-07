#pragma once

#include "portfolio.h"

class PortfolioIncrease : public PortfolioCommand
{
public:
    PortfolioIncrease(TgBot::Bot &bot, const std::int64_t chatId);
    ~PortfolioIncrease();

protected:
    void sendInstructions() override;
    const std::string getDescription() override;
    void commandLogic() override;
};