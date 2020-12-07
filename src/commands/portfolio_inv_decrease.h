#pragma once

#include "portfolio.h"

class PortfolioInversionDecrease : public PortfolioCommand
{
public:
    PortfolioInversionDecrease(TgBot::Bot &bot, const std::int64_t chatId);
    ~PortfolioInversionDecrease();

protected:
    void sendInstructions() override;
    const std::string getDescription() override;
    void commandLogic() override;
};