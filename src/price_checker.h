#pragma once

#include <string>
#include <map>
#include <chrono>

typedef std::chrono::high_resolution_clock Time;
typedef std::chrono::milliseconds ms;
typedef std::chrono::duration<float> fsec;
typedef std::chrono::time_point<std::chrono::_V2::system_clock, std::chrono::_V2::system_clock::duration> t;

#define CACHE_PRICE_SECS 5

class PriceChecker
{
public:
    double FetchPrice(const std::string& ticker);
    void SetApiKey(const std::string& apiKey);
private:
    bool ShouldFetchPrice(const std::string& ticker);
    void CachePrice(const std::string& ticker, double price);
private:
    std::string m_apiKey;
    std::map<std::string, double> m_cachedPrices;
    std::map<std::string, t> m_cachedTimes;
};