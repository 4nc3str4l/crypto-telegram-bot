#pragma once

#include "command.h"

class PricenCommand : public Command
{
public:
    PricenCommand(const std::int64_t chatId);
    ~PricenCommand();

protected:
    void sendInstructions() override;
    const std::string getDescription() override;
    void commandLogic() override;
};