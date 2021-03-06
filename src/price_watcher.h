#pragma once

#include <thread>
#include <mutex>
#include <vector>
#include <string>
#include <optional>

#include <tgbot/tgbot.h>
#include "data/model.h"
#include <cstdint>

#define INVALID_CONVERTION 0

class PriceWatcher
{
public:
    static PriceWatcher &shared_instance()
    {
        static PriceWatcher watcher;
        return watcher;
    }
    ~PriceWatcher();
    void start(TgBot::Bot *bot);
    void stop();
    unsigned long addConvertion(const double orAmount, const std::string &orTicker,
                                const double targetAmount, const std::string &targetTicker,
                                const std::int32_t investorId);
    int deleteConvertion(unsigned long convId, const std::int32_t investorId);
    std::string getConvertionListFor(std::int32_t investorId);

    std::optional<tracking_convertion> getConvertionWithId(unsigned long convId);

private:
    PriceWatcher(){};
    void checkLoop();
    void loadInitialData();

private:
    TgBot::Bot *m_bot;
    bool m_running;
    int m_checkInterval = 60;
    std::thread t;
    std::mutex m_mutex;
    std::vector<tracking_convertion> m_trackingConvertions;
    unsigned long tConvId = 1;
};