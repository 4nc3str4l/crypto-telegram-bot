#include "price_watcher.h"

#include <chrono>
#include <iostream>
#include <fmt/core.h>

#include "utils.h"
#include "data/persistence.h"
#include "constants.h"

void PriceWatcher::start(TgBot::Bot *bot)
{
    m_bot = bot;
    m_running = true;
    this->loadInitialData();
    t = std::thread(&PriceWatcher::checkLoop, this);
}

void PriceWatcher::loadInitialData()
{
    for (const tracking_convertion& tc : Persistence::shared_instance().data.convertions)
    {
        this->tConvId = tc.id > this->tConvId ? tc.id : this->tConvId;
        m_trackingConvertions.push_back(tc);
    }

    if (Persistence::shared_instance().data.convertions.size() > 0 && this->tConvId >= 1)
    {
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
    while (m_running)
    {
        std::lock_guard<std::mutex> guard(mtx);
        for (const tracking_convertion& conv : m_trackingConvertions)
        {
            std::string s = fmt::format("Or {} {} Target: {} {}\n", conv.orQuantity, conv.orTicker, conv.targetQuantity, conv.tTicker);
            fmt::print(s);
            bool convertionOk = isConvertionReady(conv);
            double progress = computeConvertionProgress(conv);
            fmt::print(fmt::format("Conversion {}% Ready {}\n", progress, convertionOk));
            if (convertionOk)
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
        std::this_thread::sleep_for(std::chrono::seconds(m_checkInterval));
    }
    std::cout << "Thread Stopped" << std::endl;
}

unsigned long PriceWatcher::addConvertion(const double orAmount, const std::string &orTicker, const double targetAmount, const std::string &targetTicker,
                                          const std::int32_t investorId)
{
    std::lock_guard<std::mutex> guard(mtx);
    unsigned long newId = tConvId++;

    // NOTE: Checks if the user is tracking convertions to higher values (to sell) or to lower (to buy)
    bool isSell = computeConv(orAmount, orTicker, targetTicker) < targetAmount; 
    m_trackingConvertions.push_back({newId, orTicker, orAmount, targetTicker, targetAmount, investorId, isSell});
    Persistence::shared_instance().saveConvertions(m_trackingConvertions);
    return newId;
}

int PriceWatcher::deleteConvertion(unsigned long convId, const std::int32_t investorId)
{
    int result = NOT_FOUND;

    std::lock_guard<std::mutex> guard(mtx);
    auto it = std::find_if(m_trackingConvertions.begin(), m_trackingConvertions.end(), 
        [convId](const tracking_convertion &c){
            return c.id == convId;
        }
    );

    if(it != m_trackingConvertions.end())
    {
        result = (*it).investorId == investorId ? OK : UNAUTHORIZED_OPERATION;
    }

    if (result == OK)
    {
        m_trackingConvertions.erase(it);
    }

    Persistence::shared_instance().saveConvertions(m_trackingConvertions);
    return result;
}

std::string PriceWatcher::getConvertionListFor(std::int32_t investorId)
{
    std::string cList;
    std::lock_guard<std::mutex> guard(mtx);
    for (int i = 0; i < m_trackingConvertions.size(); ++i)
    {
        const tracking_convertion &c = m_trackingConvertions[i];
        if (c.investorId == investorId)
        {
            cList += fmt::format("ID={} {} {} to {} {}\n", c.id, c.orQuantity, c.orTicker, c.targetQuantity, c.tTicker);
        }
    }
    return cList;
}

std::optional<tracking_convertion> PriceWatcher::getConvertionWithId(unsigned long convId)
{
    std::lock_guard<std::mutex> guard(mtx);
    for (int i = 0; i < m_trackingConvertions.size(); ++i)
    {
        const tracking_convertion& c = m_trackingConvertions[i];
        if (c.id == convId)
        {
            return c;
        }
    }
    return std::nullopt;;
}

PriceWatcher::~PriceWatcher()
{
    m_running = false;
    t.join();
}