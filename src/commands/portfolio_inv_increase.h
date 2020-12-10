#pragma once

#include "portfolio.h"

class PortfolioInversionIncrease : public PortfolioCommand
{
public:
    PortfolioInversionIncrease(const std::int64_t chatId);
    ~PortfolioInversionIncrease();

protected:
    void sendInstructions() override;
    const std::string getDescription() override;
    void commandLogic() override;
};