#pragma once

#include "portfolio.h"

class PortfolioDecrease : public PortfolioCommand
{
public:
    PortfolioDecrease(const std::int64_t chatId);
    ~PortfolioDecrease();

protected:
    void sendInstructions() override;
    const std::string getDescription() override;
    void commandLogic() override;
};