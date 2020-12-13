#pragma once

#include <string>
#include <sol/sol.hpp>

#define SCRIPTS_PATH "./lua_commands/"

inline static sol::state lua{};

typedef std::function<void(const std::vector<std::string>&, const std::int64_t)> cmd_func;
typedef std::function<int(void)> fnum_args;
typedef std::function<std::string(void)> fstring_data;


void setupLua();
bool executeLuaCommand(const std::string& comand, const std::vector<std::string>& args, const std::int64_t chatId);

double checkPrice(const std::string& ticker);
double sendMessage(const std::string& message, const std::int64_t chatId);
double strToDouble(const std::string& d);