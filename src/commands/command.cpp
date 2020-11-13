#include "command.h"

#include <fmt/core.h>

Command::Command(const std::string &command, const unsigned short numArguments,
                    const TgBot::Bot& bot, const std::int64_t chatId)
{
    this->m_command = command;
    this->m_numArguments = numArguments;
    this->m_bot = bot;
    this->m_chatId = chatId;
}

void Command::execute(const std::vector<std::string> &arguments, const Investor &caller)
{
    printMsg("Executing...");
    this->m_arguments = arguments;
    if (this->IsNumArgmentsCorrect())
    {
        printError(fmt::format("Incorrect number of arguments got {} expected", this->arguments.size() -1, this->m_numArguments));
        return;
    }

}

bool Command::isNumArgmentsCorrect()
{
    return this->m_arguments.size() - 1 == this->m_numArguments;
}

double Command::getDouble() 
{
    if(this->m_indexRead >= m_arguments.size())
    {
        printError("Attempted to read double when no more params can be retreived.");
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
        printError(ftm::format("Could not convert {} to double", this->m_arguments[this->m_indexRead]);
    }
    return value;
}

int Command::getInt()
{
    if(this->m_indexRead >= m_arguments.size())
    {
        printError("Attempted to read int when no more params can be retreived.");
        return -1;
    }

    int value = -1;
    try
    {
        value = std:::stoi(this->m_arguments[this->m_indexRead]);
        ++this->m_indexRead;
    }
    catch(std::exception& e)
    {
        printError(ftm::format("Could not convert {} to integer", this->m_arguments[this->m_indexRead]);
    }
    return value;
}

std::string& Command::getString()
{
    if(this->m_indexRead >= m_arguments.size())
    {
        printError("Attempted to read int when no more params can be retreived.");
        return std::string::empty;
    }

    return this->m_arguments[this->m_indexRead++];
}

void Command::printError(const std::string& error)
{
    std::string message = fmt::format("ERROR [{}] {}", this->m_command, error);
    std::cout << message << std::endl;;
}

void Command::printMsg(const std::string& msg)
{
    std::string message = fmt::format("INFO [{}] {}", this->m_command, msg);
    std::cout << message << std::endl;
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
