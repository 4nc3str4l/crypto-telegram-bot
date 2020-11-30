#pragma once

#include "command.h"

class UnTrackConvertionCommand : public Command
{
public:
    UnTrackConvertionCommand(TgBot::Bot &bot, const std::int64_t chatId);
    ~UnTrackConvertionCommand();

protected:
    void sendInstructions();
    const std::string getDescription();
    void commandLogic();
};