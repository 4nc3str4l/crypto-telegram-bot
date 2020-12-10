#pragma once

#include "command.h"

class HelpCommand : public Command
{
public:
    HelpCommand(const std::int64_t chatId);
    ~HelpCommand();

protected:
    void sendInstructions() override;
    const std::string getDescription() override;
    void commandLogic() override;
};