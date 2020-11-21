#pragma once
#include "model.h"
#include <cstdint>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

#define FILE_PATH "app_data.json"
#define VERSION "1.0.0"

class Persistence
{
public:
    Persistence();
    bool isWhiteListed(const std::int32_t id);
    investor* getInvestor(const std::int32_t id);
private:
    bool isFilePresent();
    void createInitialFile();
    void loadData();
    void loadWhiteListed(const json& data);
    void loadUsers(const json& data);
private:
    app_data data;
};
