
#include "utils.h"

#include <fmt/core.h>

#include "data/model.h"
#include "price_checker.h"
#include "constants.h"


double computeConv(const double amount, const std::string& ticker, const std::string& targetTicker)
{
    double originFiatVal = getFiatValue(amount, ticker);
    double targetPrice = PriceChecker::shared_instance().fetchPrice(targetTicker);
    return originFiatVal / targetPrice;
}

double getFiatValue(const double amount, const std::string& ticker)
{
    double price = PriceChecker::shared_instance().fetchPrice(ticker);
    return amount * price;
}

bool isConvertionReady(const tracking_convertion& conv)
{
    double orFiat = getFiatValue(conv.orQuantity, conv.orTicker); 
    double targetFiat = getFiatValue(conv.targetQuantity, conv.tTicker);
    return computeConvertionProgress(conv) >= 100;
}

double computeConvertionProgress(const tracking_convertion& conv)
{
    double orFiat = getFiatValue(conv.orQuantity, conv.orTicker); 
    double targetFiat = getFiatValue(conv.targetQuantity, conv.tTicker);
    return orFiat / targetFiat * 100;
}

double computeConvertion(const tracking_convertion& conv)
{
    return computeConv(conv.orQuantity, conv.orTicker, conv.tTicker);
}

std::string getPorfolioInformation(const portfolio& p)
{
    double totalHoldings = 0;
    double gains = 0;
    double performace = 0;
    std::string assetString;
    for(const asset& a : p.assets)
    {
        double assetValue = getFiatValue(a.quantity, a.ticker);
        totalHoldings += assetValue;
        assetString += fmt::format("*{}:* {} ({}{})\n", a.ticker, a.quantity, assetValue, CURRENCY_TICKER);
    }
    gains = totalHoldings - p.invested;
    performace = ((totalHoldings / p.invested) - 1) * 100;
    std::string info(fmt::format("ID=*{}* *{}*\n", p.id,  p.name));
    info += fmt::format("Invested: {}{}\n", p.invested, CURRENCY_TICKER);
    info += fmt::format("Tota Holdings: {}{}\n", totalHoldings, CURRENCY_TICKER);
    info += fmt::format("Gains: {}{}\n", gains, CURRENCY_TICKER);
    info += fmt::format("Performance: {}%\n", performace);
    info += fmt::format("*Assets:*\n\n");
    info += assetString;
    return info;
}