#pragma once

#define SOL_EXCEPTIONS_SAFE_PROPAGATION 1
#define SOL_ALL_SAFETIES_ON 1
#include <string>
#include <sol/sol.hpp>
#include <mutex>

#define SCRIPTS_PATH "./lua_commands/"

typedef std::function<void(const std::vector<std::string>&, const std::int64_t)> cmd_func;
typedef std::function<int(void)> fnum_args;
typedef std::function<std::string(void)> fstring_data;


double check_price(const std::string& ticker);
void sendMessage(const std::string& message, const std::int64_t chatId);
double strToDouble(const std::string& d);

class Scripting
{
public:
    static Scripting &shared_instance()
    {
        static Scripting scripting;
        return scripting;
    }

    bool executeLuaCommand(const std::string& comand, const std::vector<std::string>& args, const std::int64_t chatId);
    std::string getCommands();

private:
    Scripting();
    void setupLua();

private:
    inline static sol::state lua{};
    std::mutex m_mutex;

};