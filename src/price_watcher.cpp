#include "price_watcher.h"

#include <chrono>
#include <iostream>

void PriceWatcher::start(TgBot::Bot* bot)
{
    m_bot = bot;
    m_running = true;
    t = std::thread(&PriceWatcher::checkLoop, this);
}

void PriceWatcher::stop()
{
    m_running = false;
}

void PriceWatcher::checkLoop()
{
    while(m_running)
    {
        std::cout << "Check Thread " << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(m_checkInterval)); 
    }

    std::cout << "Thread Stopped" << std::endl;
}

PriceWatcher::~PriceWatcher()
{
    m_running = false;
    t.join();
    
}