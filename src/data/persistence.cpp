#include "persistence.h"

#include <iomanip>
#include <iostream>
#include <fstream>
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

Persistence::Persistence()
{
  bool shouldCreateFile = !this->IsFilePresent();
  if (shouldCreateFile)
  {
    std::cout << "File should be created " << std::endl;
    this->CreateInitialFile();
  }
  else
  {
    std::cout << "File is present" << std::endl;
  }
  this->LoadData();
}

bool Persistence::IsFilePresent()
{
  return fs::exists(FILE_PATH);
}

void Persistence::CreateInitialFile()
{
  // Generate a JSON FILE
  json j;
  j["whitelisted-ids"] = json::array();
  j["version"] = VERSION;
  j["user-data"] = json::array();
  std::ofstream o(FILE_PATH);
  o << std::setw(4) << j << std::endl;
  o.close();
}

void Persistence::LoadData()
{
  std::ifstream i(FILE_PATH);
  json j;
  i >> j;
  i.close();
  this->LoadWhiteListed(j);
}

void Persistence::LoadWhiteListed(const json &data)
{
  // Load whitelisted Ips
  auto ids = data["whitelisted-ids"];
  for (auto id : ids)
  {
    this->data.whitelisted_ids.push_back(id);
  }
  std::cout << "Num whitelisted ids " << this->data.whitelisted_ids.size() << std::endl;
}

bool Persistence::IsWhiteListed(const std::int32_t id)
{
  // If there is no one whitelisted this bot is publix
  if (this->data.whitelisted_ids.size() == 0)
  {
    return true;
  }

  for (long wid : this->data.whitelisted_ids)
  {
    if (wid == id)
    {
      return true;
    }
  }
  return false;
}
