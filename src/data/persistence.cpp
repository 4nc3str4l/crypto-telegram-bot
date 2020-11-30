#include "persistence.h"

#include <iomanip>
#include <iostream>
#include <fstream>
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

Persistence::Persistence()
{
    bool shouldCreateFile = !this->isFilePresent();
    if (shouldCreateFile)
    {
        std::cout << "File should be created " << std::endl;
        this->createInitialFile();
    }
    else
    {
        std::cout << "File is present" << std::endl;
    }
    this->loadData();
}

bool Persistence::isFilePresent()
{
    return fs::exists(FILE_PATH);
}

void Persistence::createInitialFile()
{
    // Generate a JSON FILE
    json j;
    j["whitelisted-ids"] = json::array();
    j["version"] = VERSION;
    j["user-data"] = json::array();
    std::ofstream o(FILE_PATH);
    o << std::setw(4) << j << std::endl;
    o.close();

    // Generate the tracking convertions file
    json tConvs;
    tConvs["tracking_convertions"] = json::array();
    std::ofstream o2(CONVERTIONS_PATH);
    o2 << std::setw(4) << tConvs << std::endl;
    o2.close();

    // Generate the portfolios file
    json portfolios;
    portfolios["portfolios"] = json::array();
    std::ofstream o3(PORTFOLIOS_PATH);
    o3 << std::setw(4) << portfolios << std::endl;
    o3.close();
}

void Persistence::saveConvertions(const std::vector<tracking_convertion> &convertions)
{

    auto arr = json::array();
    for (const tracking_convertion &c : convertions)
    {
        json obj = {
            {"id", c.id},
            {"orTicker", c.orTicker},
            {"orQuantity", c.orQuantity},
            {"tTicker", c.tTicker},
            {"targetQuantity", c.targetQuantity},
            {"investorId", c.investorId}};

        arr.push_back(obj);
    }

    json toPersist;
    toPersist["tracking_convertions"] = arr;
    m_mut.lock();
    std::ofstream o(CONVERTIONS_PATH);
    o << std::setw(4) << toPersist << std::endl;
    o.close();
    m_mut.unlock();
}

void Persistence::savePortfolios(const std::vector<portfolio> &portfolios)
{
    auto arr = json::array();
    for (const portfolio &c : portfolios)
    {
        json portolioObj = {
            {"id", c.id},
            {"investorId", c.investorId},
            {"invested", c.invested},
            {"name", c.name},
        };

        auto assets = json::array();
        for (asset a : c.assets)
        {
            json asset = {
                {"ticker", a.ticker},
                {"quantity", a.quantity}};

            assets.push_back(asset);
        }
        portolioObj["assets"] = assets;
        arr.push_back(portolioObj);
    }

    json toPersist;
    toPersist["portfolios"] = arr;
    m_mut.lock();
    std::ofstream o(PORTFOLIOS_PATH);
    o << std::setw(4) << toPersist << std::endl;
    o.close();
    m_mut.unlock();
}

void Persistence::loadData()
{
    std::ifstream i(FILE_PATH);
    json j;
    i >> j;
    i.close();
    this->loadWhiteListed(j);

    std::ifstream i2(CONVERTIONS_PATH);
    json j2;
    i2 >> j2;
    i2.close();
    this->loadTrackingConvertions(j2);

    std::ifstream i3(PORTFOLIOS_PATH);
    json j3;
    i3 >> j3;
    i3.close();
    this->loadTrackingPortfolios(j3);
}

void Persistence::loadWhiteListed(const json &data)
{
    // Load whitelisted Ips
    auto ids = data["whitelisted-ids"];
    for (auto id : ids)
    {
        this->data.whitelisted_ids.push_back(id);
    }
    std::cout << "Num whitelisted ids " << this->data.whitelisted_ids.size() << std::endl;
}

void Persistence::loadTrackingConvertions(const json &data)
{
    auto savedConvertions = data["tracking_convertions"];
    for (auto c : savedConvertions)
    {
        this->data.convertions.push_back({c["id"],
                                          c["orTicker"],
                                          c["orQuantity"],
                                          c["tTicker"],
                                          c["targetQuantity"],
                                          c["investorId"]});
    }
}

void Persistence::loadTrackingPortfolios(const json &d)
{
    auto savedPortfolios = d["portfolios"];
    for (auto p : savedPortfolios)
    {
        portfolio portfolio = {
            p["id"],
            p["investorId"],
            p["invested"],
            p["name"],
        };

        auto assets = p["assets"];
        for (auto a : assets)
        {
            portfolio.assets.push_back({a["ticker"],
                                        a["quantity"]});
        }
        data.portfolios.push_back(portfolio);
    }
}

bool Persistence::isWhiteListed(const std::int32_t id)
{
    // If there is no one whitelisted this bot is public
    if (this->data.whitelisted_ids.size() == 0)
    {
        return true;
    }

    for (long wid : this->data.whitelisted_ids)
    {
        if (wid == id)
        {
            return true;
        }
    }
    return false;
}
