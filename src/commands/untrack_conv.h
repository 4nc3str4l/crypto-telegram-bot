#pragma once

#include "command.h"

class UnTrackConvertionCommand : public Command
{
public:
    UnTrackConvertionCommand(TgBot::Bot &bot, const std::int64_t chatId);
    ~UnTrackConvertionCommand();

protected:
    void sendInstructions() override;
    const std::string getDescription() override;
    void commandLogic() override;
};