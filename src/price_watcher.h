#pragma once

#include <thread>
#include <vector>

#include <tgbot/tgbot.h>
#include "data/model.h"

class PriceWatcher
{
public:
    static PriceWatcher &shared_instance() {static PriceWatcher watcher; return watcher;}
    ~PriceWatcher();
    void start(TgBot::Bot* bot);
    void stop();
private:
    PriceWatcher(){};
    void checkLoop();
private:
    TgBot::Bot* m_bot;
    bool m_running;
    int m_checkInterval = 10;
    std::thread t;
    std::vector<tracking_convertion> m_trackingConvertions;
};