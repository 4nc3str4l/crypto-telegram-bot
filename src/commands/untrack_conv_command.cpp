#include "untrack_conv_command.h"

#include <fmt/core.h>

#include "../price_checker.h"
#include "../constants.h"
#include "../price_watcher.h"


UnTrackConvertionCommand::UnTrackConvertionCommand(TgBot::Bot& bot, const std::int64_t chatId) :
Command(COMMAND_TRACK_CONV, 1, bot, chatId){
}

void UnTrackConvertionCommand::sendInstructions()
{
    send(fmt::format("Invalid Command usage /{} <id>. Example: /{} 1", m_command, m_command));
}

const std::string UnTrackConvertionCommand::getDescription()
{
    return std::string("Deletes a tracking convertion by id");
}

UnTrackConvertionCommand::~UnTrackConvertionCommand(){}

void UnTrackConvertionCommand::commandLogic()
{
    unsigned long id = getUnsignedLong();
    
    if(id == INVALID_CONVERTION)
    {
        send(fmt::format("Invalid id {}", id));
        return;
    }

    int status = PriceWatcher::shared_instance().deleteConvertion(id, m_chatId);
    switch (status)
    {
        case OK:
            send(fmt::format("Convertion {} deleted!", id));
            break;
        case UNAUTHORIZED_OPERATION:
            send(fmt::format("Convertion {} not found", id));
            printMsg(fmt::format("User {} is trying to delete convertion with id {}", m_chatId, id), false);
            break;
        case NOT_FOUND:
            send(fmt::format("Convertion {} not found", id));
            break;

    }
}