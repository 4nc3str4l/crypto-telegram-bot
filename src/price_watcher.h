#pragma once

#include <thread>
#include <mutex>
#include <vector>

#include <tgbot/tgbot.h>
#include "data/model.h"
#include <cstdint>

class PriceWatcher
{
public:
    static PriceWatcher &shared_instance() {static PriceWatcher watcher; return watcher;}
    ~PriceWatcher();
    void start(TgBot::Bot* bot);
    void stop();
    bool addConvertion( const double orAmount, const std::string& orTicker,
                        const double targetAmount, const std::string& targetTicker,
                        const std::int32_t investorId);
private:
    PriceWatcher(){};
    void checkLoop();
private:
    TgBot::Bot* m_bot;
    bool m_running;
    int m_checkInterval = 10;
    std::thread t;
    std::mutex mtx;
    std::vector<tracking_convertion> m_trackingConvertions;
};