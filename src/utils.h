#pragma once

#include <string>

struct tracking_convertion;
struct portfolio;

double computeConv(const double amount, const std::string &ticker, const std::string &targetTicker);
double getFiatValue(const double amount, const std::string &ticker);
bool isConvertionReady(const tracking_convertion &conv);
double computeConvertionProgress(const tracking_convertion &conv);
double computeConvertion(const tracking_convertion &conv);
std::string getPorfolioInformation(const portfolio &p);
std::string roundTo(const double x, const unsigned int decimals);
