#pragma once

#include "portfolio.h"

class PortfolioTargetSet : public PortfolioCommand
{
public:
    PortfolioTargetSet(const std::int64_t chatId);
    ~PortfolioTargetSet();

protected:
    void sendInstructions() override;
    const std::string getDescription() override;
    void commandLogic() override;
};