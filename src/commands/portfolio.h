#pragma once

#include "command.h"

class PortfolioCommand : public Command
{
public:
    PortfolioCommand(const std::string &name, const unsigned short numArguments, TgBot::Bot &bot, const std::int64_t chatId);
    ~PortfolioCommand();
    bool getPortfolioId();

protected:
    unsigned long m_Id;
};