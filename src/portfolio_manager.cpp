#include "portfolio_manager.h"

#include "./data/persistence.h"
#include "./data/model.h"

#include "constants.h"
#include "utils.h"

PortfolioManager::PortfolioManager()
{
    loadPortfolios();
}

void PortfolioManager::loadPortfolios()
{
    for (const portfolio& p : Persistence::shared_instance().data.portfolios)
    {
        m_Portfolios.push_back(p);
        m_PortfolioIdCounter = p.id > m_PortfolioIdCounter ? p.id : m_PortfolioIdCounter;
    }
    ++m_PortfolioIdCounter;
}

unsigned long PortfolioManager::addPortfolio(const std::int32_t investorId, const std::string name)
{
    std::lock_guard<std::mutex> guard(m_Mtx);
    unsigned int id = m_PortfolioIdCounter++;
    m_Portfolios.push_back({id,
                            investorId,
                            0,
                            name});
    Persistence::shared_instance().savePortfolios(m_Portfolios);
    return id;
}

int PortfolioManager::removePortfolio(const unsigned long id, const std::int32_t investorId)
{
    int result = NOT_FOUND;
    std::lock_guard<std::mutex> guard(m_Mtx);

    auto it = std::find_if(m_Portfolios.begin(), m_Portfolios.end(), 
        [id](const portfolio &p){
            return p.id == id;
        }
    );

    if(it != m_Portfolios.end())
    {
        result = (*it).investorId == investorId ? OK : UNAUTHORIZED_OPERATION;
    }

    if (result == OK)
    {
        m_Portfolios.erase(it);
    }

    Persistence::shared_instance().savePortfolios(m_Portfolios);
    return result;
}

bool PortfolioManager::isOwnerOf(const std::int32_t investorId, const unsigned long id)
{
    bool isOwner = false;
    std::lock_guard<std::mutex> guard(m_Mtx);
    for (int i = m_Portfolios.size() - 1; i >= 0; --i)
    {
        const portfolio &p = m_Portfolios[i];
        if (p.id == id)
        {
            isOwner = p.investorId == investorId;
            break;
        }
    }
    return isOwner;
}

void PortfolioManager::updateInvested(const unsigned long id, double amount)
{
    std::lock_guard<std::mutex> guard(m_Mtx);
    for (int i = m_Portfolios.size() - 1; i >= 0; --i)
    {
        portfolio &p = m_Portfolios[i];
        if (p.id == id)
        {
            p.invested = amount;
            break;
        }
    }
    Persistence::shared_instance().savePortfolios(m_Portfolios);
}

void PortfolioManager::setAsset(std::string ticker, double amount, const unsigned long portfolioId)
{
    if (amount < 0)
    {
        return;
    }

    std::lock_guard<std::mutex> guard(m_Mtx);
    portfolio *p;
    bool found = false;

    for (int i = m_Portfolios.size() - 1; i >= 0; --i)
    {
        p = &m_Portfolios[i];
        if (p->id == portfolioId)
        {
            found = true;
            break;
        }
    }

    if (found)
    {
        bool assetFound = false;
        int idx = 0;
        for (asset &a : p->assets)
        {
            if (a.ticker == ticker)
            {
                a.quantity = amount;
                assetFound = true;
                break;
            }
            ++idx;
        }
        if (!assetFound && amount > 0)
        {
            p->assets.push_back({ticker, amount});
        }
        else if (amount == 0)
        {
            p->assets.erase(p->assets.begin() + idx);
        }
    }
    Persistence::shared_instance().savePortfolios(m_Portfolios);
}

asset PortfolioManager::getPortfolioAsset(const unsigned long id, const std::string &ticker)
{
    std::lock_guard<std::mutex> guard(m_Mtx);
    asset toReturn;
    toReturn.quantity = INVALID_ASSET;
    for (int i = m_Portfolios.size() - 1; i >= 0; --i)
    {
        const portfolio &p = m_Portfolios[i];
        if (p.id == id)
        {
            for (const asset &a : p.assets)
            {
                if (a.ticker == ticker)
                {
                    toReturn = {a.ticker, a.quantity};
                    break;
                }
            }
        }
    }
    return toReturn;
}

portfolio PortfolioManager::getPortfolio(const unsigned long id)
{
    std::lock_guard<std::mutex> guard(m_Mtx);
    portfolio toReturn;
    toReturn.id = INVALID_PORTFOLIO;
    for (int i = m_Portfolios.size() - 1; i >= 0; --i)
    {
        portfolio &p = m_Portfolios[i];
        if (p.id == id)
        {
            toReturn = m_Portfolios[i];
            break;
        }
    }
    return toReturn;
}

std::string PortfolioManager::listPortfolios(const std::int32_t investorId)
{
    std::lock_guard<std::mutex> guard(m_Mtx);
    std::string portfolios;
    int numPortfolios = 0;
    for (const portfolio &p : m_Portfolios)
    {
        if (p.investorId == investorId)
        {
            portfolios += getPorfolioInformation(p);
            numPortfolios++;
        }
    }

    if (numPortfolios == 0)
    {
        return std::string("You haven't created a portfolio yet use /pnew <name> to create 1.");
    }

    return portfolios;
}