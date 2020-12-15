#pragma once

#include <string>
#include <unordered_map>
#include <chrono>
#include <mutex>

typedef std::chrono::high_resolution_clock Time;
typedef std::chrono::milliseconds ms;
typedef std::chrono::duration<float> fsec;
typedef std::chrono::time_point<std::chrono::_V2::system_clock, std::chrono::_V2::system_clock::duration> t;

#define CACHE_PRICE_SECS 5

class PriceChecker
{
public:
    static PriceChecker &shared_instance()
    {
        static PriceChecker checker;
        return checker;
    }
    double fetchPrice(const std::string &ticker);
    void setApiKey(const std::string &apiKey);

private:
    bool shouldFetchPrice(const std::string &ticker);
    void cachePrice(const std::string &ticker, double price);

private:
    std::string m_apiKey;
    std::mutex m_mutex;
    std::unordered_map<std::string, double> m_cachedPrices;
    std::unordered_map<std::string, t> m_cachedTimes;
};