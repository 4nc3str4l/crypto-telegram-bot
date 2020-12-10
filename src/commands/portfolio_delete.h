#pragma once

#include "portfolio.h"

class PortfolioDelete : public PortfolioCommand
{
public:
    PortfolioDelete(const std::int64_t chatId);
    ~PortfolioDelete();

protected:
    void sendInstructions() override;
    const std::string getDescription() override;
    void commandLogic() override;
};