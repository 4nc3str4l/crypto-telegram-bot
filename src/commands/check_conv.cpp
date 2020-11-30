#include "check_conv.h"

#include <fmt/core.h>

#include "../price_checker.h"
#include "../constants.h"
#include "../price_watcher.h"
#include "../utils.h"

ConvertionCheckCommand::ConvertionCheckCommand(TgBot::Bot &bot, const std::int64_t chatId) : Command(COMMAND_CHECK_CONV, 1, bot, chatId)
{
}

void ConvertionCheckCommand::sendInstructions()
{
    send(fmt::format("Invalid Command usage {} <id>. Example: {} 1", m_command, m_command));
}

const std::string ConvertionCheckCommand::getDescription()
{
    return std::string("Deletes a tracking convertion by id");
}

ConvertionCheckCommand::~ConvertionCheckCommand() {}

void ConvertionCheckCommand::commandLogic()
{
    unsigned long id = getUnsignedLong();

    tracking_convertion c = PriceWatcher::shared_instance().getConvertionWithId(id);

    if (c.id == INVALID_CONVERTION || c.investorId != m_chatId)
    {
        send(fmt::format("Convertion {} not found", id));
        return;
    }

    double curr = computeConvertion(c);
    double progress = computeConvertionProgress(c);
    std::string toSend = fmt::format(
        "ID={} Progress={}%. Now with {}{} you could have {}{} (you wanted {})",
        id, progress, c.orQuantity, c.orTicker, curr, c.tTicker, c.targetQuantity, c.tTicker);
    send(toSend);
}