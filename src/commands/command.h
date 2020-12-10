#pragma once

#include <vector>
#include <string>
#include <cstdint>
#include <map>

#include <tgbot/tgbot.h>

struct Investor;
class PriceChecker;

class Command
{
public:
  Command(const std::string &command, const unsigned short numArguments, const std::int64_t chatId);
  virtual ~Command(){};
  bool isNumArgmentsCorrect();
  void execute(const std::vector<std::string> &arguments);
  inline static void setupTgBot(TgBot::Bot &bot){ m_bot = &bot; }
  static void ssend(const std::string &msg, const std::int64_t chatId);
  void send(const std::string &message);
protected:
  double getDouble();
  int getInt();
  unsigned long getUnsignedLong();
  const std::string &getString();
  const std::string &getTicker();

  // Abstract functions
  virtual void sendInstructions() = 0;
  virtual const std::string getDescription() = 0;
  virtual void commandLogic() = 0;
  void printError(const std::string &error, bool send);
  void printMsg(const std::string &msg, bool send);

protected:
  std::string m_command;
  inline static TgBot::Bot *m_bot = nullptr;
  std::int64_t m_chatId;
  unsigned short m_numArguments;
  unsigned short m_indexRead = 1;
  std::vector<std::string> m_arguments;
};
