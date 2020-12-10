#pragma once

#include <string>

void setupLua();
double checkPrice(const std::string& ticker);
double sendMessage(const std::string& message, const std::int64_t chatId);
bool executeLuaCommand(const std::string& comand, const std::int64_t chatId);