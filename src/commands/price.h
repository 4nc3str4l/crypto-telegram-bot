#pragma once

#include "command.h"

class PriceCommand : public Command
{
public:
    PriceCommand(const std::int64_t chatId);
    ~PriceCommand();

protected:
    void sendInstructions() override;
    const std::string getDescription() override;
    void commandLogic() override;
};