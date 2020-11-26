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
    std::int32_t investorId;
    double invested;
    std::string name;
    std::vector<asset> assets;
};

struct tracking_convertion {
    unsigned long id;
    std::string orTicker;
    double orQuantity;
    std::string tTicker;
    double targetQuantity;
    std::int32_t investorId;
};

struct app_data {
    std::vector<long> whitelisted_ids;
    std::vector<tracking_convertion> convertions;
    std::vector<portfolio> portfolios;
};

