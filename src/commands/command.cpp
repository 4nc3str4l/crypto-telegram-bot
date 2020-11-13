#include "command.h"

#include <fmt/core.h>

Command::Command(const std::string &command, const unsigned short numArguments,
                    TgBot::Bot& bot, const std::int64_t chatId)
{
    this->m_command = command;
    this->m_numArguments = numArguments;
    this->m_bot = &bot;
    this->m_chatId = chatId;
}

void Command::execute(const std::vector<std::string> &arguments)
{
    printMsg("Executing...", false);
    this->m_arguments = arguments;
    if (!this->isNumArgmentsCorrect())
    {
        printError(
            fmt::format("Incorrect number of arguments got {} expected", this->m_arguments.size() -1, this->m_numArguments),
            true
        );
        return;
    }
    commandLogic();
}

bool Command::isNumArgmentsCorrect()
{
    return this->m_arguments.size() - 1 == this->m_numArguments;
}

double Command::getDouble() 
{
    if(this->m_indexRead >= m_arguments.size())
    {
        printError("Attempted to read double when no more params can be retreived.", true);
        return -1;
    }

    double value = -1;
    try
    {
        value = std::stod(this->m_arguments[this->m_indexRead]);
        ++this->m_indexRead;
    }
    catch(std::exception& e)
    {
        printError(fmt::format("Could not convert {} to double", this->m_arguments[this->m_indexRead]), true);
    }
    return value;
}

int Command::getInt()
{
    if(this->m_indexRead >= m_arguments.size())
    {
        printError("Attempted to read int when no more params can be retreived.", false);
        return -1;
    }

    int value = -1;
    try
    {
        value = std::stoi(this->m_arguments[this->m_indexRead]);
        ++this->m_indexRead;
    }
    catch(std::exception& e)
    {
        printError(fmt::format("Could not convert {} to integer", this->m_arguments[this->m_indexRead]), false);
    }
    return value;
}

const std::string& Command::getString()
{

    if(this->m_indexRead >= m_arguments.size())
    {
        printError("Attempted to read int when no more params can be retreived.", false);
        static const std::string empty = "";
        return empty;
    }

    return this->m_arguments[this->m_indexRead++];
}

const std::string& Command::getTicker()
{
    if(this->m_indexRead >= m_arguments.size())
    {
        printError("Attempted to read int when no more params can be retreived.", false);
        static const std::string empty = "";
        return empty;
    }

    std::string& ticker = this->m_arguments[this->m_indexRead++];
    std::transform(ticker.begin(), ticker.end(), ticker.begin(), ::toupper);
    return ticker;
}

void Command::printError(const std::string& error, bool send=false)
{
    std::string message = fmt::format("ERROR [{}] {}", this->m_command, error);
    std::cout << message << std::endl;
    
    if(send)
    {
        this->send(message);
    }
}

void Command::printMsg(const std::string& msg, bool send=false)
{
    std::string message = fmt::format("INFO [{}] {}", this->m_command, msg);
    std::cout << message << std::endl;

    if(send)
    {
        this->send(message);
    }
}

void Command::send(const std::string& message)
{
    try
    {
        this->m_bot->getApi().sendMessage(m_chatId, message);
    }
    catch(std::exception& e)
    {
        printError(fmt::format("Could not send message: {} to chat id {}", message, m_chatId));
    }
}
