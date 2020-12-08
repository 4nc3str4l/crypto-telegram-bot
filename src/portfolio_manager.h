#pragma once

#include <mutex>
#include <vector>
#include <cstdint>
#include "./data/model.h"
#include <optional>

class PortfolioManager
{
public:
    static PortfolioManager &shared_instance()
    {
        static PortfolioManager manager;
        return manager;
    }
    unsigned long addPortfolio(const std::int32_t investorId, const std::string name);
    int removePortfolio(const unsigned long id, const std::int32_t investorId);
    bool isOwnerOf(const std::int32_t investorId, const unsigned long id);
    void updateInvested(const unsigned long id, double amount);
    void setAsset(std::string ticker, double amount, const unsigned long portfolioId);
    std::optional<portfolio> getPortfolio(const unsigned long id);
    std::string listPortfolios(const std::int32_t investorId);
    std::optional<asset> getPortfolioAsset(const unsigned long id, const std::string &ticker);

private:
    PortfolioManager();
    void loadPortfolios();
    unsigned long m_PortfolioIdCounter = 0;

    std::mutex m_Mtx;
    std::vector<portfolio> m_Portfolios;
};