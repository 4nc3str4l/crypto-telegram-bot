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
    bool IsWhiteListed(const std::int32_t id);
private:
    bool IsFilePresent();
    void CreateInitialFile();
    void LoadData();
    void LoadWhiteListed(const json& data);
    void LoadUsers(const json& data);
private:
    app_data data;
};