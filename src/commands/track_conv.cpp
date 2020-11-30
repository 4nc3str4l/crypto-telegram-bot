#include "track_conv.h"

#include <fmt/core.h>

#include "../price_checker.h"
#include "../constants.h"
#include "../price_watcher.h"

TrackConvertionCommand::TrackConvertionCommand(TgBot::Bot &bot, const std::int64_t chatId) : Command(COMMAND_TRACK_CONV, 4, bot, chatId)
{
}

void TrackConvertionCommand::sendInstructions()
{
    send(fmt::format("Invalid Command usage {} <quanity> <ticker> <target_quantity> <target_ticker>. Example: {} 1 btc 1000000 USDT", m_command, m_command));
}

const std::string TrackConvertionCommand::getDescription()
{
    return std::string("Sets and alarm that will alert you when a certain conversion is met.");
}

TrackConvertionCommand::~TrackConvertionCommand() {}

void TrackConvertionCommand::commandLogic()
{
    double amount = getDouble();
    std::string ticker = getTicker();
    if (ticker.size() == 0)
    {
        return;
    }

    double tAmount = getDouble();
    std::string tTicker = getTicker();
    if (tTicker.size() == 0)
    {
        return;
    }

    unsigned long convId = PriceWatcher::shared_instance().addConvertion(amount,
                                                                         ticker,
                                                                         tAmount,
                                                                         tTicker,
                                                                         m_chatId);

    double price = PriceChecker::shared_instance().fetchPrice(ticker);
    if (convId != INVALID_CONVERTION)
    {
        send(fmt::format("ID={} Tracking when {}{} will be worth {}{}", convId, amount, ticker, tAmount, tTicker));
    }
    else
    {
        send(fmt::format("Could not track convertion: {}{} to {}{}", amount, ticker, tAmount, tTicker));
    }
}