#pragma once

#include "portfolio.h"

class PortfolioCheck : public PortfolioCommand
{
public:
    PortfolioCheck(const std::int64_t chatId);
    ~PortfolioCheck();

protected:
    void sendInstructions() override;
    const std::string getDescription() override;
    void commandLogic() override;
};