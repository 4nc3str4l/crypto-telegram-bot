#include "price_checker.h"

#include <iostream>
#include <nlohmann/json.hpp>
#include <algorithm>
#include "cpr/cpr.h"
#include "constants.h"
#include "fmt/core.h"

using json = nlohmann::json;

void PriceChecker::setApiKey(const std::string &apiKey)
{
    this->m_apiKey = apiKey;
}

double PriceChecker::fetchPrice(const std::string &ticker)
{
    if (!this->shouldFetchPrice(ticker))
    {
        std::lock_guard<std::mutex> guard(m_mutex);
        double price = this->m_cachedPrices[ticker];
        return price;
    }

    std::cout << "Fetching price " << ticker << std::endl;

    cpr::Response r = cpr::Get(cpr::Url(
        std::string("https://api.nomics.com/v1/currencies/ticker?key=") +
        this->m_apiKey +
        std::string("&ids=") +
        std::string(ticker) +
        std::string("&interval=1d,30d&convert=") +
        std::string(CURRENCY) +
        std::string("&per-page=1&page=1").c_str()));
    int code = r.status_code;
    if (code == 200)
    {
        auto jsdata = json::parse(r.text.c_str());
        if (jsdata.is_array() && jsdata.size() > 0)
        {
#if DEBUG_MODE
            std::cout << jsdata << std::endl;
#endif
            auto price = jsdata[0]["price"];
            std::string s = price.dump();
            s.erase(std::remove(s.begin(), s.end(), '\"'), s.end());
            double dPrice = std::stod(s);
            this->cachePrice(ticker, dPrice);
            return dPrice;
        }
        else
        {
            return -1;
        }
    }
    else
    {
        fmt::print("Error in request code={} {}\n\n {} \n", r.status_code, r.text.c_str(), r.url.c_str());
        return -1;
    }
}

bool PriceChecker::shouldFetchPrice(const std::string &ticker)
{
    std::lock_guard<std::mutex> guard(m_mutex);
    if (this->m_cachedPrices.find(ticker) == this->m_cachedPrices.end())
    {
        return true;
    }

    fsec delta = Time::now() - this->m_cachedTimes[ticker];
    ms duration = std::chrono::duration_cast<ms>(delta);
    return duration > std::chrono::seconds(CACHE_PRICE_SECS);
}

void PriceChecker::cachePrice(const std::string &ticker, double price)
{
    t to = Time::now();
    std::lock_guard<std::mutex> guard(m_mutex);
    this->m_cachedPrices[ticker] = price;
    this->m_cachedTimes[ticker] = to;
}