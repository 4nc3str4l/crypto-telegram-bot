#pragma once

#include "command.h"

class ListTrackingConvertions : public Command
{
public:
    ListTrackingConvertions(const std::int64_t chatId);
    ~ListTrackingConvertions();

protected:
    void sendInstructions() override;
    const std::string getDescription() override;
    void commandLogic() override;
};