#include "command.h"

#include "tgbot/types/GenericReply.h"
#include <fmt/core.h>
#include <memory>

#include "../price_checker.h"

Command::Command(const std::string &command, const unsigned short numArguments, const std::int64_t chatId)
{
    this->m_command = command;
    this->m_numArguments = numArguments;
    this->m_chatId = chatId;
}

void Command::execute(const std::vector<std::string> &arguments)
{
    printMsg("Executing...", false);
    this->m_arguments = arguments;
    if (!this->isNumArgmentsCorrect())
    {
        printError(
            fmt::format("Incorrect number of arguments got {} expected {}", this->m_arguments.size() - 1, this->m_numArguments),
            true);
        sendInstructions();
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
    if (this->m_indexRead >= m_arguments.size())
    {
        printError("Attempted to read double when no more params can be retreived.", true);
        sendInstructions();
        return -1;
    }

    double value = -1;
    try
    {
        value = std::stod(this->m_arguments[this->m_indexRead]);
        ++this->m_indexRead;
    }
    catch (std::exception &e)
    {
        printError(fmt::format("Could not convert {} to double", this->m_arguments[this->m_indexRead]), true);
        sendInstructions();
    }
    return value;
}

int Command::getInt()
{
    if (this->m_indexRead >= m_arguments.size())
    {
        printError("Attempted to read int when no more params can be retreived.", false);
        sendInstructions();
        return -1;
    }

    int value = -1;
    try
    {
        value = std::stoi(this->m_arguments[this->m_indexRead]);
        ++this->m_indexRead;
    }
    catch (std::exception &e)
    {
        printError(fmt::format("Could not convert {} to integer", this->m_arguments[this->m_indexRead]), false);
        sendInstructions();
    }
    return value;
}

unsigned long Command::getUnsignedLong()
{
    if (this->m_indexRead >= m_arguments.size())
    {
        printError("Attempted to read int when no more params can be retreived.", false);
        sendInstructions();
        return 0;
    }

    unsigned long value = 0;
    try
    {
        value = std::stoul(this->m_arguments[this->m_indexRead]);
        ++this->m_indexRead;
    }
    catch (std::exception &e)
    {
        printError(fmt::format("Could not convert {} to unsigned long", this->m_arguments[this->m_indexRead]), false);
        sendInstructions();
    }
    return value;
}

const std::string &Command::getString()
{

    if (this->m_indexRead >= m_arguments.size())
    {
        printError("Attempted to read int when no more params can be retreived.", false);
        static const std::string empty = "";
        return empty;
    }

    return this->m_arguments[this->m_indexRead++];
}

const std::string &Command::getTicker()
{
    static const std::string empty = "";
    // TODO: We could check if a ticker is correct (need a way to validate tickers)
    if (this->m_indexRead >= m_arguments.size())
    {
        printError("Attempted to read int when no more params can be retreived.", false);
        sendInstructions();
        return empty;
    }

    std::string &ticker = this->m_arguments[this->m_indexRead++];
    std::transform(ticker.begin(), ticker.end(), ticker.begin(), ::toupper);

    double price = PriceChecker::shared_instance().fetchPrice(ticker);
    std::cout << price << std::endl;
    if (price == -1)
    {
        printError("Incorrect Ticker", true);
        sendInstructions();
        return empty;
    }

    return ticker;
}

void Command::printError(const std::string &error, bool send = false)
{
    std::string message = fmt::format("{}: {}", this->m_command, error);
    std::cout << "[ERROR] " << message << std::endl;

    if (send)
    {
        this->send(message);
    }
}

void Command::printMsg(const std::string &msg, bool send = false)
{
    std::string message = fmt::format("{}: {}", this->m_command, msg);
    std::cout << "[INFO] " << message << std::endl;

    if (send)
    {
        this->send(message);
    }
}

void Command::ssend(const std::string &message, const std::int64_t chatId)
{
    try
    {
        m_bot->getApi().sendMessage(chatId, message, false, 0, std::make_shared<TgBot::GenericReply>(), "Markdown");
    }
    catch (std::exception &e)
    {
        fmt::print("Could not send message: {} to chat id {}:\n", message, chatId);
        std::cout << e.what() << std::endl;
    }
}

void Command::send(const std::string &msg)
{
    ssend(msg, m_chatId);
}