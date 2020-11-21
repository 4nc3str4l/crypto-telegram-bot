#include "price_watcher.h"

#include <chrono>
#include <iostream>
#include <fmt/core.h>

void PriceWatcher::start(TgBot::Bot* bot)
{
    m_bot = bot;
    m_running = true;
    t = std::thread(&PriceWatcher::checkLoop, this);
    this->addConvertion(
        1, 
        std::string("BTC"),
        20000,
        std::string("USDT"),
        579393170    
    );

}

void PriceWatcher::stop()
{
    m_running = false;
}

void PriceWatcher::checkLoop()
{
    while(m_running)
    {
        mtx.lock();
        for(tracking_convertion conv : m_trackingConvertions)
        {
            std::string s = fmt::format("Or {} {} Target: {} {}\n", conv.orQuantity, conv.orTicker, conv.targetQuantity, conv.tTicker); 
            fmt::print(s);
        }
        mtx.unlock();
        std::this_thread::sleep_for(std::chrono::seconds(m_checkInterval)); 
    }
    std::cout << "Thread Stopped" << std::endl;
}

bool PriceWatcher::addConvertion(const double orAmount, const std::string& orTicker, const double targetAmount, const std::string& targetTicker,
                        const std::int32_t investorId)
{
    mtx.lock();
    m_trackingConvertions.push_back({std::string("BTC"), 1, std::string("USDT"), 20000, investorId});
    mtx.unlock();
    return true;   
}

PriceWatcher::~PriceWatcher()
{
    m_running = false;
    t.join();
    
}