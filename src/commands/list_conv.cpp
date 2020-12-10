#include "list_conv.h"

#include <fmt/core.h>

#include "../price_checker.h"
#include "../constants.h"
#include "../price_watcher.h"

ListTrackingConvertions::ListTrackingConvertions(const std::int64_t chatId) : Command(COMMAND_LIST_CONV, 0, chatId)
{
}

void ListTrackingConvertions::sendInstructions()
{
    send(fmt::format("Invalid Command usage {} <id>. Example: {} ", m_command, m_command));
}

const std::string ListTrackingConvertions::getDescription()
{
    return std::string("Lists all the tracking convertions");
}

ListTrackingConvertions::~ListTrackingConvertions() {}

void ListTrackingConvertions::commandLogic()
{
    std::string toSend = PriceWatcher::shared_instance().getConvertionListFor(m_chatId);
    if (toSend.size() == 0)
    {
        send("No Convertions Found!");
        return;
    }
    send(toSend);
}