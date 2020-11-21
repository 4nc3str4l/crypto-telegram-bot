#pragma once

#include <vector>
#include <string>
#include <cstdint>

struct asset {
    std::string ticker;
    double quantity;
};

struct portfolio {
    unsigned long id;
    double invested;
    std::string name;
    std::vector<asset> assets;
};

struct tracking_convertion {
    std::string orTicker;
    double orQuantity;
    std::string tTicker;
    double targetQuantity;
    std::int32_t investorId;
};

struct investor {
    std::int32_t id;
    std::string name;
    std::vector<portfolio> portfolios;
    std::vector<tracking_convertion> convertions;
};

struct app_data {
    std::vector<long> whitelisted_ids;
    std::vector<investor> investors;
};

double compute_convertion(const tracking_convertion& conv);
