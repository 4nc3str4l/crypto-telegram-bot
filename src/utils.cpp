
#include "utils.h"

#include <fmt/core.h>
#include <iomanip>
#include <sstream>

#include "data/model.h"
#include "price_checker.h"
#include "constants.h"

double computeConv(const double amount, const std::string &ticker, const std::string &targetTicker)
{
    double originFiatVal = getFiatValue(amount, ticker);
    double targetPrice = PriceChecker::shared_instance().fetchPrice(targetTicker);
    return originFiatVal / targetPrice;
}

double getFiatValue(const double amount, const std::string &ticker)
{
    double price = PriceChecker::shared_instance().fetchPrice(ticker);
    return amount * price;
}

bool isConvertionReady(const tracking_convertion &conv)
{
    double progress = computeConvertionProgress(conv);
    if(conv.isSell){
        return progress >= 100;
    }else{
        return progress > 0;
    }

}

double computeConvertionProgress(const tracking_convertion &conv)
{
    double orFiat = getFiatValue(conv.orQuantity, conv.orTicker);
    double targetFiat = getFiatValue(conv.targetQuantity, conv.tTicker);
    double progress =  orFiat / targetFiat * 100;

    if(conv.isSell){
        return progress;
    }else{
        // If the convertion is to buy we need to change a bit the progress
        return 100 - progress; // 100 - 130 = -30%
    }
}

double computeConvertion(const tracking_convertion &conv)
{
    return computeConv(conv.orQuantity, conv.orTicker, conv.tTicker);
}

std::string getPorfolioInformation(const portfolio &p)
{
    double totalHoldings = 0;
    double gains = 0;
    double performace = 0;
    std::string assetString;
    for (const asset &a : p.assets)
    {
        double assetValue = getFiatValue(a.quantity, a.ticker);
        totalHoldings += assetValue;
        assetString += fmt::format("*{}:* {} ({}{})\n", a.ticker, a.quantity, roundTo(assetValue, 2), CURRENCY_TICKER);
    }
    gains = totalHoldings - p.invested;
    performace = ((totalHoldings / p.invested) - 1) * 100;
    std::string info(fmt::format("ID=*{}* *{}*\n", p.id, p.name));
    info += fmt::format("Invested: {}{}\n", p.invested, CURRENCY_TICKER);
    info += fmt::format("Total Holdings: {}{}\n", roundTo(totalHoldings, 2), CURRENCY_TICKER);
    info += fmt::format("Gains: {}{}\n", roundTo(gains, 2), CURRENCY_TICKER);
    if (p.invested > 0)
    {
        info += fmt::format("Performance: {}%\n", roundTo(performace, 2));
    }
    info += fmt::format("*Assets:*\n");
    info += assetString;
    return info;
}

std::string roundTo(const double x, const unsigned int decimals){
    std::stringstream stream;
    stream << std::fixed << std::setprecision(decimals) << x;
    return stream.str();
}