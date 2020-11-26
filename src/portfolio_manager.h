#pragma once

#include <mutex>
#include <vector>
#include <cstdint>

struct portfolio;

#define INVALID_PORTFOLIO 0

class PortfolioManager 
{
public:
    static PortfolioManager &shared_instance() {static PortfolioManager manager; return manager;}
    unsigned long addPortfolio(const std::int32_t investorId, const std::string name);
    int removePortfolio(const unsigned long id, const std::int32_t investorId);
    bool isOwnerOf(const std::int32_t investorId, const unsigned long id);
    void updateInvested(const unsigned long id, double amount);
    void setAsset(std::string ticker, double amount);
    portfolio getPortfolio(const unsigned long id);
    std::string listPortfolios(const std::int32_t investorId);    
private: 
    PortfolioManager();
    loadPortfolios();
    unsigned long m_PortfolioIdCounter = 1;

    std::mutex m_Mtx;
    std::vector<portfolio> m_Portfolios;
};