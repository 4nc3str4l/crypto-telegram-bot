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
    for(portfolio p : Persistence::shared_instance().data.portfolios)
    {
        m_Portfolios.push_back(p);
        m_PortfolioIdCounter = p.id > m_PortfolioIdCounter ? p.id : m_PortfolioIdCounter;
    }
    ++m_PortfolioIdCounter;
}

unsigned long PortfolioManager::addPortfolio(const std::int32_t investorId, const std::string name)
{
    m_Mtx.lock();
    unsigned int id = m_PortfolioIdCounter++;
    m_Portfolios.push_back({
        id,
        investorId,
        0,
        name
    });
    Persistence::shared_instance().savePortfolios(m_Portfolios);
    m_Mtx.unlock();
    return id;
}

int PortfolioManager::removePortfolio(const unsigned long id, const std::int32_t investorId)
{
    int result = NOT_FOUND; 
    m_Mtx.lock();
    int idx = -1;
    for(int i = m_Portfolios.size() -1; i >= 0; --i)
    {
        const portfolio& p = m_Portfolios[i];
        if(p.id == id)
        {
            if(p.investorId == investorId)
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
        m_Portfolios.erase(m_Portfolios.begin() + idx);
    }

    Persistence::shared_instance().savePortfolios(m_Portfolios);
    m_Mtx.unlock();
    return result;
}

bool PortfolioManager::isOwnerOf(const std::int32_t investorId, const unsigned long id)
{
    bool isOwner = false;
    m_Mtx.lock();
    for(int i = m_Portfolios.size() -1; i >= 0; --i)
    {
        const portfolio& p = m_Portfolios[i];
        if(p.id == id)
        {
            isOwner = p.investorId == investorId;
            break;
        }
    }
    m_Mtx.unlock();
    return isOwner;
}

void PortfolioManager::updateInvested(const unsigned long id, double amount)
{
    m_Mtx.lock();
    for(int i = m_Portfolios.size() -1; i >= 0; --i)
    {
        portfolio& p = m_Portfolios[i];
        if(p.id == id)
        {
            p.invested = amount;
            break;
        }
    }
    m_Mtx.unlock();
}

void PortfolioManager::setAsset(std::string ticker, double amount, const unsigned long portfolioId)
{
    m_Mtx.lock();
    portfolio* p;
    bool found = false;
    for(int i = m_Portfolios.size() -1; i >= 0; --i)
    {
        p = &m_Portfolios[i];
        if(p->id == portfolioId)
        {
            found = true; 
            break;
        }
    }

    if(found)
    {
        bool assetFound = false;
        for(asset& a : p->assets)
        {
            if(a.ticker == ticker)
            {
                a.quantity = amount;
                assetFound = true;
                break;
            }
        }

        if(!assetFound)
        {
            p->assets.push_back({ticker, amount});
        }
    }
    m_Mtx.unlock();
}

portfolio PortfolioManager::getPortfolio(const unsigned long id)
{
    m_Mtx.lock();
    portfolio toReturn;
    toReturn.id = INVALID_PORTFOLIO;
    for(int i = m_Portfolios.size() -1; i >= 0; --i)
    {
        portfolio& p = m_Portfolios[i];
        if(p.id == id)
        {
            toReturn = m_Portfolios[i];
            break;
        }
    }
    m_Mtx.unlock();
    return toReturn;
}

std::string PortfolioManager::listPortfolios(const std::int32_t investorId)
{
    std::string portfolios;
    m_Mtx.lock();
    for(const portfolio& p : m_Portfolios)
    {
        if(p.investorId == investorId)
        {
            portfolios += getPorfolioInformation(p);
        }
    }
    m_Mtx.unlock();
    return portfolios;
}