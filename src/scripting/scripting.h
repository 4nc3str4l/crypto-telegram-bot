#pragma once

#include <string>
#include <sol/sol.hpp>

inline static sol::state lua{};

typedef std::function<void(const std::string, const std::int64_t)> cmd_func;

void setupLua();
double checkPrice(const std::string& ticker);
double sendMessage(const std::string& message, const std::int64_t chatId);
bool executeLuaCommand(const std::string& comand, const std::int64_t chatId);