#include "check_conv.h"

#include <fmt/core.h>
#include <optional>

#include "../price_checker.h"
#include "../constants.h"
#include "../price_watcher.h"
#include "../utils.h"

ConvertionCheckCommand::ConvertionCheckCommand(const std::int64_t chatId) : Command(COMMAND_CHECK_CONV, 1, chatId)
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

    std::optional<tracking_convertion> optC = PriceWatcher::shared_instance().getConvertionWithId(id);

    if (!optC.has_value() || optC.value().investorId != m_chatId)
    {
        send(fmt::format("Convertion {} not found", id));
        return;
    }

    tracking_convertion& c = optC.value();

    double curr = computeConvertion(c);
    double progress = computeConvertionProgress(c);

    std::string toSend = fmt::format(
        "ID={} Progress={}%. Now with {}{} you could have {}{} (you wanted {})",
        id, roundTo(progress, 2), c.orQuantity, c.orTicker, roundTo(curr, 2), c.tTicker, c.targetQuantity, c.tTicker);
    send(toSend);
}