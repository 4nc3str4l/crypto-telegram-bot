#pragma once

#include "command.h"

class ConvertionCheckCommand : public Command
{
public:
    ConvertionCheckCommand(const std::int64_t chatId);
    ~ConvertionCheckCommand();

protected:
    void sendInstructions() override;
    const std::string getDescription() override;
    void commandLogic() override;
};