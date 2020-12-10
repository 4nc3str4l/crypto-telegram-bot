#pragma once

#include "command.h"

class PortfolioNew : public Command
{
public:
    PortfolioNew(const std::int64_t chatId);
    ~PortfolioNew();

protected:
    void sendInstructions() override;
    const std::string getDescription() override;
    void commandLogic() override;
};