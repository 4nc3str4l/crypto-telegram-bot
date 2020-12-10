#pragma once

#include "portfolio.h"

class PortfolioSet : public PortfolioCommand
{
public:
    PortfolioSet(const std::int64_t chatId);
    ~PortfolioSet();

protected:
    void sendInstructions() override;
    const std::string getDescription() override;
    void commandLogic() override;
};