#pragma once

#include "command.h"

class TrackConvertionCommand : public Command
{
public:
    TrackConvertionCommand(TgBot::Bot &bot, const std::int64_t chatId);
    ~TrackConvertionCommand();

protected:
    void sendInstructions();
    const std::string getDescription();
    void commandLogic();
};