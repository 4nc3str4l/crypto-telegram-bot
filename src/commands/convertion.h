#pragma once

#include "command.h"

class ConvertionCommand : public Command
{
public:
    ConvertionCommand(TgBot::Bot &bot, const std::int64_t chatId);
    ~ConvertionCommand();

protected:
    void sendInstructions() override;
    const std::string getDescription() override;
    void commandLogic() override;
};