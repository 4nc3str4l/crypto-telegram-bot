#pragma once

#include <tgbot/tgbot.h>
#include <map>

#include "commands/command.h"

const std::vector<std::string> getCommandArguments(const std::string &command);
void exec(Command &c, const std::int64_t chatId, const std::string &message);
void parseMessage(const std::string& message, const std::int64_t chatId);