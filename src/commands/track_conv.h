#pragma once

#include "command.h"

class TrackConvertionCommand : public Command
{
public:
    TrackConvertionCommand(const std::int64_t chatId);
    ~TrackConvertionCommand();

protected:
    void sendInstructions() override;
    const std::string getDescription() override;
    void commandLogic() override;
};