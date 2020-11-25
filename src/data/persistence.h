#pragma once
#include "model.h"
#include <cstdint>
#include <nlohmann/json.hpp>
#include <vector>
#include <mutex>

using json = nlohmann::json;

#define FILE_PATH "app_data.json"
#define CONVERTIONS_PATH "convertions.json"
#define VERSION "1.0.0"

struct tracking_convertion;

class Persistence
{
public:
    static Persistence &shared_instance() {static Persistence persistence; return persistence;}
    bool isWhiteListed(const std::int32_t id);
    investor* getInvestor(const std::int32_t id);
    void saveConvertions(const std::vector<tracking_convertion>& convertions);
private:
    Persistence();
    bool isFilePresent();
    void createInitialFile();
    void loadData();
    void loadWhiteListed(const json& data);
    void loadTrackingConvertions(const json& data);
    void loadUsers(const json& data);
    std::mutex m_mut;
public:
    app_data data;
};
