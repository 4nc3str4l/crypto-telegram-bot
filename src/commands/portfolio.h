#pragma once

#include "command.h"

class PortfolioCommand : public Command
{
public:
    PortfolioCommand(const std::string &name, const unsigned short numArguments, const std::int64_t chatId);
    ~PortfolioCommand();
    bool getPortfolioId();

protected:
    unsigned long m_Id;
};