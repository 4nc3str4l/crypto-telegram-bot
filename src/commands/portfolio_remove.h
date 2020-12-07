#pragma once

#include "portfolio.h"

class PortfolioRemove : public PortfolioCommand
{
public:
    PortfolioRemove(TgBot::Bot &bot, const std::int64_t chatId);
    ~PortfolioRemove();

protected:
    void sendInstructions() override;
    const std::string getDescription() override;
    void commandLogic() override;
};