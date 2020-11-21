
#include "utils.h"

#include "data/model.h"
#include "price_checker.h"

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