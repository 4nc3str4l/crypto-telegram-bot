#pragma once

#include "command.h"

class ListTrackingConvertions : public Command
{
public:
    ListTrackingConvertions(TgBot::Bot &bot, const std::int64_t chatId);
    ~ListTrackingConvertions();

protected:
    void sendInstructions();
    const std::string getDescription();
    void commandLogic();
};