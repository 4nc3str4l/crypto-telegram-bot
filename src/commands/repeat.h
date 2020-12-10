#pragma once

#include "command.h"

class RepeatCommand : public Command
{
public:
    RepeatCommand(const std::int64_t chatId);
    ~RepeatCommand();

protected:
    void saveLastCommand();
    void sendInstructions() override;
    const std::string getDescription() override;
    void commandLogic() override;
};