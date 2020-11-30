#include "price_watcher.h"

#include <chrono>
#include <iostream>
#include <fmt/core.h>

#include "utils.h"
#include "data/persistence.h"
#include "constants.h"


void PriceWatcher::start(TgBot::Bot* bot)
{
    m_bot = bot;
    m_running = true;
    this->loadInitialData();
    t = std::thread(&PriceWatcher::checkLoop, this);
}

void PriceWatcher::loadInitialData()
{
    for(tracking_convertion tc : Persistence::shared_instance().data.convertions)
    {
        this->tConvId = tc.id > this->tConvId ? tc.id : this->tConvId;
        m_trackingConvertions.push_back(tc);
    }

    if(Persistence::shared_instance().data.convertions.size() > 0 && this->tConvId >= 1){
        this->tConvId++;
    }

    fmt::print(fmt::format("Loaded {} convertions, current id {}\n", m_trackingConvertions.size(), this->tConvId));
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
            bool convertionOk = isConvertionReady(conv);
            double progress = computeConvertionProgress(conv);
            fmt::print(fmt::format("Conversion {}% Ready {}\n", progress, convertionOk));
            if(convertionOk)
            {
                double currentConv = computeConv(conv.orQuantity, conv.orTicker, conv.tTicker);
                std::string msg = fmt::format("ID={} Now with {}{} you can have {}{} (you wanted {}{})",
                                              conv.id,
                                              conv.orQuantity,
                                              conv.orTicker,
                                              currentConv,
                                              conv.tTicker,
                                              conv.targetQuantity,
                                              conv.tTicker);
                m_bot->getApi().sendMessage(conv.investorId, msg);
            }
        }
        mtx.unlock();
        std::this_thread::sleep_for(std::chrono::seconds(m_checkInterval)); 
    }
    std::cout << "Thread Stopped" << std::endl;
}

unsigned long PriceWatcher::addConvertion(const double orAmount, const std::string& orTicker, const double targetAmount, const std::string& targetTicker,
                        const std::int32_t investorId)
{
    mtx.lock();
    unsigned long newId = tConvId++;
    m_trackingConvertions.push_back({newId, orTicker, orAmount, targetTicker, targetAmount, investorId});
    Persistence::shared_instance().saveConvertions(m_trackingConvertions);
    mtx.unlock();
    return newId;   
}

int PriceWatcher::deleteConvertion(unsigned long convId, const std::int32_t investorId)
{
    int idx = -1;
    int result = NOT_FOUND;

    mtx.lock();
    for(int i = m_trackingConvertions.size() -1; i >= 0; --i)
    {
        const tracking_convertion& c = m_trackingConvertions[i];
        if(c.id == convId)
        {
            // If the user owns the convertion we can delete it
            if(c.investorId == investorId)
            {
                result = OK;
                idx = i;
            }
            else
            {
                result = UNAUTHORIZED_OPERATION;
            }
            break;
        }
    }

    if(result == OK)
    {
        m_trackingConvertions.erase(m_trackingConvertions.begin() + idx);
    }
    Persistence::shared_instance().saveConvertions(m_trackingConvertions);
    mtx.unlock();
    return result;
}

std::string PriceWatcher::getConvertionListFor(std::int32_t investorId)
{
    std::string cList;
    mtx.lock();
    for(int i = 0; i < m_trackingConvertions.size(); ++i)
    {
        const tracking_convertion& c = m_trackingConvertions[i];
        if(c.investorId == investorId)
        {
            cList += fmt::format("ID={} {} {} to {} {}\n", c.id, c.orQuantity, c.orTicker, c.targetQuantity, c.tTicker);
        }
    }
    mtx.unlock();
    return cList;
}

tracking_convertion PriceWatcher::getConvertionWithId(unsigned long convId)
{
    mtx.lock();
    tracking_convertion conv;
    conv.id = INVALID_CONVERTION;
    for(int i = 0; i < m_trackingConvertions.size(); ++i)
    {
        const tracking_convertion c = m_trackingConvertions[i];
        if(c.id == convId)
        {
            conv = c;
            break;
        }
    }
    mtx.unlock();
    return conv;
}

PriceWatcher::~PriceWatcher()
{
    m_running = false;
    t.join();   
}