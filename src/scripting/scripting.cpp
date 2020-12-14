#include "./scripting.h"

#include <tgbot/tgbot.h>
#include "tgbot/types/GenericReply.h"

#include <fmt/core.h>
#include <vector>

#include <iostream>
#include <memory>
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

#include "../price_checker.h"
#include "../commands/command.h"


Scripting::Scripting()
{
    setupLua();
}

void Scripting::setupLua()
{
    lua.open_libraries(sol::lib::base);
    lua.set_function("check_price", &checkPrice);
    lua.set_function("send_message", &sendMessage);
    lua.set_function("to_double", &strToDouble);
    
    lua["commands"] = lua.create_table();
    lua["utils"] = lua.create_table();

    for(const auto& entry : fs::directory_iterator(SCRIPTS_PATH))
    {
        try
        {
            lua.script_file(entry.path());
            std::cout << "Loaded "<< entry.path() << std::endl;
        }
        catch(std::exception &e)
        {
            std::cerr << e.what() << std::endl;
        }   
    }

    const fstring_data& data = lua["utils"]["get_commands"];
    data();
}

double checkPrice(const std::string& ticker)
{
    return PriceChecker::shared_instance().fetchPrice(ticker);
}

double sendMessage(const std::string& message, const std::int64_t chatId)
{
    Command::ssend(message, chatId);
}

double strToDouble(const std::string& d)
{
    return std::stod(d);
}

bool Scripting::executeLuaCommand(const std::string& comand, const std::vector<std::string>& args, const std::int64_t chatId)
{
    std::lock_guard<std::mutex> guard(m_mutex);
    auto cmd = lua["commands"][comand];
    if(cmd.valid())
    {
        try
        {
            const fnum_args& numArgs = cmd["num_arguments"];
            unsigned int currentArgs = args.size() - 1;
            if(currentArgs != numArgs())
            {
                Command::ssend(fmt::format("Incorrect number of arguments {} != {}", currentArgs, numArgs()), chatId);
                const fstring_data& help = cmd["help"];
                Command::ssend(help(), chatId);
            }
            else
            {
                const cmd_func& commandLogic = cmd["logic"];
                commandLogic(args, chatId);
            }
            
            return true;
        }
        catch(std::exception& e)
        {
            std::cout << e.what() << std::endl;
            return false;
        }
    }
    return false;
}

std::string Scripting::getCommands()
{
    std::lock_guard<std::mutex> guard(m_mutex);
    const fstring_data& extraCommands = lua["utils"]["get_commands"];
    return lua["utils"]["get_commands"]();
}